#include "Scene.h"
#include "Camera.h"
#include "MathEngine.h"
#include "Sphere.h"
#include "Triangle.h"
#include "SceneObject.h"
#include "ImagePlane.h"
#include "FocusPlane.h"
#include "IntersectionInfo.h"
#include "EasyBMP.h"
#include "DirectionalLight.h"
#include "AmbientLight.h"
#include "PointLight.h"
#include "AreaLight.h"
#include <math.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>

Scene::Scene(std::string _sceneFileName) 
    : sceneFileName_(_sceneFileName),
      superSamplingFactor_(1.f),
      samplesPerAreaLight_(1),
      dofSamples_(1),
      focalLength_(1.f),
      apertureSize_(1.f),
      pathTracingSamples_(500),
      renderMode_(rayTracing_) {}

void Scene::parse() {

    std::ifstream sceneFileStream(sceneFileName_.c_str());

    if (sceneFileStream.fail()) {
        std::cerr << "Unable to open '" << sceneFileName_ << "'" << std::endl;
        exit(1);
    }

    char line[1024];
    while (!sceneFileStream.eof()) {
        std::stringstream ss;
        sceneFileStream.getline(line, 1023);
        ss.str(line);
        std::string command;
        ss >> command;

        if (command == "Camera") {
			float ex, ey, ez, ux, uy, uz, lx, ly, lz, fov, asp;
			ss >> ex >> ey >> ez >> ux >> uy >> uz >> lx >> ly >> 
                  lz >> fov >> asp;
			Point3f eye(ex, ey, ez);
			Vector3f up(ux, uy, uz);
			Point3f lookAt(lx, ly, lz);
            fov = fov * M_PI / 180.f;
			camera_ = new Camera(eye, up, lookAt, fov, asp);
            Vector3f a(lookAt-eye);
            Vector3f b(up);
            Vector3f w(a);
            w.normalize();
            Vector3f u(cross(b,w));
            u.normalize();
            Vector3f v(cross(w,u));
            v.normalize();
            camera_->wIs(w);
            camera_->uIs(u);
            camera_->vIs(v);
            Point3f c = eye+w;
            float y = tan(fov/2.0f);
            float x = tan(asp*fov/2.0f);
            Point3f ll = c+(x*u)-(y*v);
            Point3f ul = c+(x*u)+(y*v);
            Point3f lr = c-(x*u)-(y*v);
            Point3f ur = c-(x*u)+(y*v);
            imagePlane_ = new ImagePlane(ll, ul, lr, ur, c);
		} else if (command == "Output") {
			int w, h;
			std::string fname;
			ss >> w >> h >> fname;
			outputWidth_ = w;
            outputHeight_ = h;
            outputFileName_ = fname;
		} else if (command == "BounceDepth") {
			int depth;
			ss >> depth;
			bounceDepth_ = depth;
		} else if (command == "SuperSamplingFactor") {
            int ssf;
            ss >> ssf;
            superSamplingFactor_ = ssf;
        } else if (command == "ShadowBias") {
			float bias;
			ss >> bias;
			shadowBias_ = bias;
		} else if (command == "SamplesPerAreaLight") {
            int s;
            ss >> s;
            samplesPerAreaLight_ = s;
        } else if (command == "PathTracingSamples" ) {
            int pts;
            ss >> pts;
            pathTracingSamples_ = pts;
        } else if (command == "DepthOfFieldSamples") {
            // camera, focal length and aperture size
            // need to be set before this one, as this
            // creates the focal plane
            int s;
            ss >> s;
            dofSamples_ = s;
            Point3f p0 = 
                camera_->eye()+camera_->w()*(1.f+focalLength_);
            Vector3f normal = camera_->w()*-1.f;
            focusPlane_ = new FocusPlane(p0, normal);

        } else if (command == "FocalLength") {
            float f;
            ss >> f;
            focalLength_ = f;
        } else if (command == "ApertureSize") {
            float a;
            ss >> a;
            apertureSize_ = a;
        }
        /*
		else
		if (command == "PushMatrix")
		{
			ParsedPushMatrix();
		}
		else
		if (command == "PopMatrix")
		{
			ParsedPopMatrix();
		}
		else
		if (command == "Rotate")
		{
			float rx, ry, rz;
			ss >> rx >> ry >> rz;
			ParsedRotate(rx, ry, rz);
		}
		else
		if (command == "Scale")
		{
			float sx, sy, sz;
			ss >> sx >> sy >> sz;
			ParsedScale(sx, sy, sz);
		}
		else
		if (command == "Translate")
		{
			float tx, ty, tz;
			ss >> tx >> ty >> tz;
			ParsedTranslate(tx, ty, tz);
		}
               */
		else if (command == "Sphere") {
			float cx, cy, cz, r;
			ss >> cx >> cy >> cz >> r;
			Point3f center(cx, cy, cz);
            Sphere* sphere = new Sphere(center, r);
            sceneObject_.push_back(new SceneObject(sphere, currentMaterial_));
		} else if (command == "Triangle") {
			float x1, y1, z1, x2, y2, z2, x3, y3, z3;
			ss >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
			Point3f v[3];
			v[0] = Point3f(x1, y1, z1);
			v[1] = Point3f(x2, y2, z2);
			v[2] = Point3f(x3, y3, z3);
            Triangle* triangle = new Triangle(v[0], v[1], v[2]);
			sceneObject_.push_back(new SceneObject(triangle, currentMaterial_));
		} else if (command == "AmbientLight") { 
            float r, g, b;
			ss >> r >> g >> b;
			Color4f col(r, g, b, 1.0);
			ambientLight_ = new AmbientLight(col);
		} else if (command == "PointLight") {
			float px, py, pz, r, g, b;
			ss >> px >> py >> pz >> r >> g >> b;
			Point3f pos(px, py, pz);
			Color4f col(r, g, b, 1.0);
            light_.push_back(new PointLight(pos, col));
        } else if (command == "AreaLight") {
            float cx, cy, cz, ax, ay, az, bx, by, bz, r, g, b;
            ss>>cx>>cy >> cz >> ax >> ay >> az >> bx >> by >> bz >> r >> g >> b;
            Point3f center(cx, cy, cz);
            Vector3f av(ax, ay, az);
            Vector3f bv(bx, by, bz);
            Color4f c(r, g ,b,1.f);
            light_.push_back(new AreaLight(center, av, bv, c));
		} else if (command == "DirectionalLight") {
			float dx, dy, dz, r, g, b;
			ss >> dx >> dy >> dz >> r >> g >> b;
			Vector3f dir(dx, dy, dz);
			Color4f col(r, g, b, 1.0);
			light_.push_back(new DirectionalLight(dir, col));
		} else if (command == "Material") {
			float ra, ga, ba, 
                rd, gd, bd, 
                rs, gs, bs,
                rr, gr, br, 
                re, ge, be,
                shine;
			ss >> ra >> ga >> ba >> rd >> gd >> bd >> rs >> gs
               >> bs >> rr >> gr >> br >> re >> ge >> be >> shine;
			Color4f amb(ra, ga, ba,1.0);
			Color4f diff(rd, gd, bd, 1.0);
			Color4f spec(rs, gs, bs, 1.0);
			Color4f mirr(rr, gr, br, 1.0);
            Color4f emitt(re, ge, be, 1.0);
			currentMaterial_ = Material(amb, diff, spec, mirr, emitt, shine);
		} else if (command == "RenderMode") {
            std::string mode;
            ss >> mode;
            if (mode == "RayTracing") {
                renderMode_ = rayTracing_;
            } else if (mode == "PathTracing") {
                renderMode_ = pathTracing_;
            } else if (mode == "PhotnMapping") {
                renderMode_ = photonMapping_;
            }
        }
	}
	sceneFileStream.close();
}

void Scene::render() {
    imagePlane_->pixelArraySizeIs(outputWidth_*outputHeight_);
    float sw = 1.f/outputWidth_;
    float sh = 1.f/outputHeight_;
    float ssw = sw/(superSamplingFactor_+1.f);
    float ssh = sh/(superSamplingFactor_+1.f);
    float percentage = 0;

    // For each pixel in the output image, sample 
    // (and possibly supersample) the image plane at u, v coordinates
    for (int x=0; x<outputWidth_; ++x) {
        percentage = x/(float)outputWidth_*100.0f;
        std::cout << std::setprecision(4) << percentage << "%" << std::endl;

        float u = static_cast<float>(x)/(outputWidth_-1.0f);
        for (int y=0; y<outputHeight_; ++y) {
            float v = static_cast<float>(y)/(outputHeight_-1.0f);

            // Supersample (send more rays within the same pixels
            // and average the resulting color).
            Color4f color(0.f, 0.f, 0.f, 1.f);  
            int superSamples = 0;
            for (int i=1; i<superSamplingFactor_+1; ++i) {
                float ssu = u-sw/2.f+i*ssw;
                for (int j=1; j<superSamplingFactor_+1; ++j) {
                    float ssv = v-sh/2.f+j*ssh;
                    if (ssu > 0.f && 
                        ssu < 1.f &&
                        ssv > 0.f &&
                        ssv < 1.f) {
                            // Point on image plane
                            Point3f imagePlanePoint = 
                                imagePlane_->imagePlanePoint(ssu,ssv);

                            // Find intersection with focus plane
                            Ray focRay = camera_->generateRay(imagePlanePoint);
                                IntersectionInfo fpii;
                                fpii = focusPlane_->rayIntersect(focRay);

                            // Generate more rays (simulate aperture)
                            std::vector<Ray> aptRays = 
                                camera_->generateApertureRays(imagePlanePoint,
                                                              fpii.point(),
                                                              apertureSize_,
                                                              dofSamples_);
                            // Trace aperture rays
                            Color4f aprtCol(0.f, 0.f, 0.f, 1.f);
                            std::vector<Ray>::const_iterator rayIt;
                            for (rayIt=aptRays.begin(); 
                                 rayIt!=aptRays.end();
                                 rayIt++) {
                                if (renderMode_ == rayTracing_) {
                                    aprtCol += traceRay(*rayIt, bounceDepth_);
                                } else if (renderMode_ == pathTracing_) {
                                    Color4f pathTraceColor(0.f, 0.f, 0.f, 1.f);
                                    for (int k=0; k<pathTracingSamples_; ++k) {
                                        pathTraceColor += tracePath(*rayIt, bounceDepth_);
                                    }
                                    aprtCol += pathTraceColor*(1.f/pathTracingSamples_);
                                } else if (renderMode_ == photonMapping_) {
                                    // photon map
                                }
                            }
                            // Average aperture rays and add to total color
                            color += aprtCol*(1.f/dofSamples_);
                            superSamples++;
                    }
                }
            }
            color = 1.f/superSamples*color;
            int index = x+outputWidth_*y;
            color.truncate();
            imagePlane_->pixelIs(index, color);
        }
    }
}

IntersectionInfo Scene::findNearestIntersection(Ray _ray, Material& _m) {
    std::vector<SceneObject*>::const_iterator it;
    float t = std::numeric_limits<float>::max();
    IntersectionInfo ii;
    for (it=sceneObject_.begin(); it!=sceneObject_.end(); ++it) {
        IntersectionInfo iiTmp;
        iiTmp = (*it)->shape()->rayIntersect(_ray);
        if (iiTmp.hitTest() == IntersectionInfo::hit() && iiTmp.t() < t) {
            ii = iiTmp;
            t = iiTmp.t();
            _m = (*it)->material();
        }
    }
    return ii;
}

Color4f Scene::traceRay(Ray _ray, int _depth) {

    Color4f c = Color4f(0.f, 0.f, 0.f, 1.f);
    if (_depth < 1) return c;

    // Check intersection with all objects in the scene and store results
    Material m;
    IntersectionInfo ii = findNearestIntersection(_ray, m);

    // If we hit something, we now have the closest t value
    // and we shade. If the surface is mirrored, we send reflective
    // rays recursively. 
    if (ii.hitTest() == IntersectionInfo::hit()) {
         c += phongShade(ii, m);
         if (m.mirror().r() > 0.f &&
             m.mirror().g() > 0.f &&
             m.mirror().b() > 0.f &&
             m.mirror().a()) {
                 Vector3f inDir = _ray.d();
                 inDir.normalize();
                 Vector3f outDir = 
                     inDir+2.f*dot(-1.0*inDir,ii.normal())*ii.normal();
                 Ray reflectingRay = Ray(ii.point(),
                                         outDir,
                                         shadowBias_,
                                         std::numeric_limits<float>::max()
                                         );
                 c += m.mirror()*traceRay(reflectingRay, _depth-1);
         }
    }
    return c;
}

Color4f Scene::phongShade(IntersectionInfo _ii, Material _m) {

    std::vector<Light*>::const_iterator it;
    Color4f totalColor = Color4f(0.f, 0.f, 0.f, 1.f);
    if (ambientLight_) totalColor += _m.ambient()*ambientLight_->color();
    Vector3f V = camera_->eye() - _ii.point();
    V.normalize();

    for (it = light_.begin(); it!=light_.end(); ++it) {

        std::vector<Vector3f> dirs = 
            (*it)->surfaceToLightDirection(_ii.point(), samplesPerAreaLight_);

        // For every light, iterate through all sample directions
        // generated.
        std::vector<Vector3f>::const_iterator dirIt = dirs.begin();
        Color4f lightColor(0.f, 0.f, 0.f, 1.f);
        for (dirIt=dirs.begin(); dirIt!=dirs.end(); dirIt++) {
  
            Vector3f L = (*dirIt);
            int dude = L.magnitude();
            // If any object is between this light and the
            // point, skip this direction in the shading calculation
            Ray occludeTestRay = Ray(_ii.point(), 
                                     L, 
                                     shadowBias_, 
                                     (*it)->maxT());
            occludeTestRay.dIs(L);
            std::vector<SceneObject*>::const_iterator objIt;
            IntersectionInfo ii;
            for (objIt=sceneObject_.begin(); 
                 objIt!=sceneObject_.end();
                 ++objIt) {
                ii = (*objIt)->shape()->rayIntersect(occludeTestRay);
                if (ii.hitTest() == IntersectionInfo::hit()) break;
            }
            if (ii.hitTest() == IntersectionInfo::miss()) {
                // Light is visible from the point, so shade
                Vector3f N = _ii.normal();
                //if (dot(N,V) < 0.f) N = -1.f*N;      
                L.normalize();
                float LdotN = dot(L, N);
                float LdotNclamped = (LdotN >= 0.f) ? LdotN : 0.f;
                lightColor += _m.diffuse()*(*it)->color()*LdotNclamped;
                Vector3f R = -1.f*L+2.f*LdotN*N;
                R.normalize();
                float RdotV = dot(R,V);
                float RdotVclamped = (RdotV >= 0.f) ? RdotV : 0.f;
                lightColor += 
                    _m.specular()*(*it)->color()*pow(RdotVclamped,_m.shine());  
            }
        } // for light sample directions
        lightColor = lightColor*(1.f/dirs.size());
        totalColor += lightColor;
    } // for all lights

    return totalColor;
}

Color4f Scene::tracePath(Ray _r, int _depth) {
    Color4f c(0.f, 0.f, 0.f, 1.f);
    if (_depth < 1) return c;
    Material m;
    IntersectionInfo ii = findNearestIntersection(_r, m);
    if (ii.hitTest() == IntersectionInfo::miss()) return c;
    Color4f emittance = m.emittance();
    if (emittance.r() > 0.01 || emittance.g() > 0.01 || emittance.b() > 0001) 
        return emittance;
    Vector3f newDir = hemisphereVector(ii.normal());
    Ray newRay(ii.point(),
               newDir,
               shadowBias_,
               std::numeric_limits<float>::max());
    float cosOmega = dot(newDir, ii.normal());
    Color4f BDRF = m.diffuse();
    Color4f reflected = tracePath(newRay, _depth-1);
    c = (BDRF*cosOmega*reflected);
    return c;

}

Vector3f Scene::hemisphereVector(Vector3f _normal) {
    Vector3f v;
    float r1 = (float)rand()/(float)RAND_MAX;
    float r2 = (float)rand()/(float)RAND_MAX;
    float x = 2.f*cos(2.f*M_PI*r1)*sqrt(r2*(1.f-r2));
    float y = 2.f*sin(2.f*M_PI*r1)*sqrt(r2*(1.f-r2));
    float z = (1.f-2.f*r2);;
    v.vectorIs(x,y,z);
    while (dot(v,_normal) < 0.0) {
        r1 = (float)rand()/(float)RAND_MAX;
        r2 = (float)rand()/(float)RAND_MAX;
        x = 2.f*cos(2.f*M_PI*r1)*sqrt(r2*(1.f-r2));
        y = 2.f*sin(2.f*M_PI*r1)*sqrt(r2*(1.f-r2));
        z = (1.f-2.f*r2);;
        v.vectorIs(x, y, z);
    }
    v.normalize();
    return v;
}

// For writing to file, the free library EasyBMP is used
void Scene::writeToFile() {
    BMP image;
    image.SetSize(outputWidth_, outputHeight_);
    image.SetBitDepth(24);
    for (int x=0; x<outputWidth_; ++x) {
        for (int y=0; y<outputHeight_; ++y) {
            int index = x+outputWidth_*(outputHeight_-y-1);
            image(x,y)->Red = 
                static_cast<int>(imagePlane_->pixel(index).r()*255.0);
            image(x,y)->Green = 
                static_cast<int>(imagePlane_->pixel(index).g()*255.0);    
            image(x,y)->Blue =
                static_cast<int>(imagePlane_->pixel(index).b()*255.0);
            image(x,y)->Alpha =
                static_cast<int>(imagePlane_->pixel(index).a()*255.0);
        }
    }
    image.WriteToFile(outputFileName_.c_str());
}

void Scene::cleanUp() {
    std::vector<SceneObject*>::iterator soit;
    for (soit=sceneObject_.begin(); soit!=sceneObject_.end(); ++soit) {
        delete *soit;
    }
    std::vector<Light*>::iterator lit;
    for (lit=light_.begin(); lit!=light_.end(); ++lit) {
        delete *lit;
    }
    delete imagePlane_;
    delete focusPlane_;
    delete ambientLight_;
    delete camera_;
}

void Scene::renderModeIs(RenderMode _mode) {
    if (renderMode_ != _mode) {
        renderMode_ = _mode;
    }
}

