#include "ofMain.h"


#define NUM 1

class ofApp : public ofBaseApp
{
    ofSpherePrimitive sphere, lightSphere, equireSphere;
    ofShader PBRShader;
    ofEasyCam cam;
    ofTexture albedo, normal, metal, aoTex, roughTex, heightTex;
    ofTexture equire;
    
    ofVec3f pos[NUM];
    ofVec3f lightPos[2];
    
    //--------------------------------------------------------------
    void setup()
    {
        sphere.set(6.0f, 30.0f);
        lightSphere.set(5, 10);
        equireSphere.set(1000, 20);
        ofDisableArbTex();
        
        PBRShader.load("shaders/pbr");
        
//        ofLoadImage(albedo, "textures/pbr/rusted_iron/albedo.png");
//        ofLoadImage(normal, "textures/pbr/rusted_iron/normal.png");
//        ofLoadImage(metal, "textures/pbr/rusted_iron/metallic.png");
//        ofLoadImage(aoTex, "textures/pbr/rusted_iron/ao.png");
//        ofLoadImage(roughTex, "textures/pbr/rusted_iron/roughness.png");
//        ofLoadImage(equire, "textures/equire.jpg");
        
            ofLoadImage(albedo, "textures/stone/rock_cliff_stylized_mossy_Diffuse.png");
            ofLoadImage(normal, "textures/stone/rock_cliff_stylized_mossy_Normal.png");
            ofLoadImage(metal, "textures/stone/rock_cliff_stylized_mossy_Glossiness.jpg");
            ofLoadImage(aoTex, "textures/stone/rock_cliff_stylized_mossy_Ambient_Occlusion.jpg");
            ofLoadImage(roughTex, "textures/stone/rock_cliff_stylized_mossy_Roughness.png");
            ofLoadImage(heightTex, "textures/stone/rock_cliff_stylized_mossy_Height.jpg");
            ofLoadImage(equire, "textures/equire.jpg");
        
        
        glEnable(GL_DEPTH_TEST);
        
        float R = 10;
//        for(int i = 0; i < 2; i++)
//        {
            lightPos[0] = ofVec3f(10, 7, 10);
            lightPos[1] = ofVec3f(ofRandom(-R, R), ofRandom(-R, R), ofRandom(-R, R));
//        }
    }
    
    
    //--------------------------------------------------------------
    void update()
    {
        cam.orbit(ofGetElapsedTimef() * 20, 200, 15);
    }
    
    
    //--------------------------------------------------------------
    void draw()
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        cam.begin();
        ofMatrix4x4 viewMatrix = ofGetCurrentViewMatrix();
        
        
        PBRShader.begin();
        PBRShader.setUniformMatrix4f("projection", cam.getProjectionMatrix());
        PBRShader.setUniformMatrix4f("view", viewMatrix);
        
        PBRShader.setUniformTexture("albedoMap", albedo, 0);
        PBRShader.setUniformTexture("normalMap", normal, 1);
        PBRShader.setUniformTexture("metallicMap", metal, 2);
        PBRShader.setUniformTexture("roughnessMap", roughTex, 3);
        PBRShader.setUniformTexture("aoMap", aoTex, 4);
        PBRShader.setUniformTexture("heightMap", heightTex, 5);
        
        PBRShader.setUniform3f("camPos", cam.getPosition());
        for(int i = 0; i < 2; i++)
        {
            PBRShader.setUniform3f("light["+to_string(i)+"].position", lightPos[i]);
        }
        PBRShader.setUniform3f("lightColor", ofVec3f(1.0f, 1.0f, 1.0f));
        PBRShader.setUniform1f("exposure", 1.0f);
        PBRShader.setUniform1f("time", ofGetElapsedTimef());
        
        
        for(int i = 0; i < NUM; i++)
        {
            ofMatrix4x4 model;
            model.scale(1.0f, 1.0f, 1.0f);
            model.translate(0.0, 0.0, 0.0);
            PBRShader.setUniformMatrix4f("model", model);
            sphere.draw();
        }
        
        
        
        PBRShader.end();
        
        equire.bind();
        equireSphere.draw();
        equire.unbind();
        
        cam.end();
    }
    
    
    //--------------------------------------------------------------
    void keyPressed(int key)
    {
        
    }
    
    
    //--------------------------------------------------------------
    void keyReleased(int key)
    {
        
    }
};


//========================================================================
int main(){
    
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3, 3);
    settings.width = 1280;
    settings.height = 720;
    settings.resizable = false;
    ofCreateWindow(settings);
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
}
