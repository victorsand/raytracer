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
#include <vector>

Scene::Scene(std::string _sceneFileName) 
    : sceneFileName_(_sceneFileName),
      superSamplingFactor_(1.f),
      samplesPerAreaLight_(1),
      dofSamples_(1),
      focalLength_(1.f),
      apertureSize_(1.f) {}

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
			float ra, ga, ba, rd, gd, bd, rs, gs, bs, rr, gr, br, shine;
			ss >> ra >> ga >> ba >> rd >> gd >> bd >> rs >> gs
               >> bs >> rr >> gr >> br >> shine;
			Color4f amb(ra, ga, ba,1.0);
			Color4f diff(rd, gd, bd, 1.0);
			Color4f spec(rs, gs, bs, 1.0);
			Color4f mirr(rr, gr, br, 1.0);
			currentMaterial_ = Material(amb, diff, spec, mirr, shine);
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
    int percentage = 0;
    int prevPercentage = -1;

    // For each pixel in the output image, sample 
    // (and possibly supersample) the image plane at u, v coordinates
    for (int x=0; x<outputWidth_; ++x) {
        prevPercentage = percentage;
        percentage = int(x/(float)outputWidth_*100.0f);
        if (percentage > prevPercentage) {
            std::cout << percentage << "%" << std::endl;
        }
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
                                aprtCol += traceRay(*rayIt, bounceDepth_);
                            }
                            // Average aperture rays and add to total color
                            aprtCol = aprtCol*(1.f/dofSamples_);
                            color += aprtCol;
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

Color4f Scene::traceRay(Ray _ray, int _depth) {

    // Check intesection with all objects in the scene
    // and store the result in an IntersectionInfo object
    std::vector<SceneObject*>::const_iterator it;
    float t = std::numeric_limits<float>::max();
    IntersectionInfo ii;
    Material m;
    Color4f c = Color4f(0.f, 0.f, 0.f, 1.f);
    for (it=sceneObject_.begin(); it!=sceneObject_.end(); ++it) {
        IntersectionInfo iiTmp;
        iiTmp = (*it)->shape()->rayIntersect(_ray);
        if (iiTmp.hitTest() == IntersectionInfo::hit() && iiTmp.t() < t) {
            ii = iiTmp;
            t = iiTmp.t();
            m = (*it)->material();
        }
    }

    // If we hit something, we now have the closest t value
    // and we shade. If the surface is mirrored, we send reflective
    // rays recursively. 
    if (ii.hitTest() == IntersectionInfo::hit()) {
         c += phongShade(ii, m);
         if (m.mirror().r() > 0.f &&
             m.mirror().g() > 0.f &&
             m.mirror().b() > 0.f &&
             m.mirror().a() > 0.f &&
             _depth > 0) {
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
                lightColor += _m.specular()*(*it)->color()*pow(RdotVclamped,_m.shine());  
            }
        } // for light sample directions
        lightColor = lightColor*(1.f/dirs.size());
        totalColor += lightColor;
    } // for all lights

    return totalColor;
}

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

