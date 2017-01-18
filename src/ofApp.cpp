#include "ofMain.h"


#define NUM 100

class ofApp : public ofBaseApp
{
    ofSpherePrimitive sphere, lightSphere;
    ofShader PBRShader;
    ofEasyCam cam;
    ofTexture albedo, normal, metal, aoTex, roughTex;
    
    ofVec3f pos[NUM];
    
    //--------------------------------------------------------------
    void setup()
    {
        sphere.set(5.0f, 30.0f);
        lightSphere.set(5, 10);
        ofDisableArbTex();
        
        PBRShader.load("shaders/pbr");
        
        ofLoadImage(albedo, "textures/pbr/rusted_iron/albedo.png");
        ofLoadImage(normal, "textures/pbr/rusted_iron/normal.png");
        ofLoadImage(metal, "textures/pbr/rusted_iron/metallic.png");
        ofLoadImage(aoTex, "textures/pbr/rusted_iron/ao.png");
        ofLoadImage(roughTex, "textures/pbr/rusted_iron/roughness.png");
        
        
        glEnable(GL_DEPTH_TEST);
        
        float R = 50;
        for(int i = 0; i < NUM; i++)
        {
            pos[i] = ofVec3f(ofRandom(-R, R), ofRandom(-R, R), ofRandom(-R, R));
        }
    }
    
    
    //--------------------------------------------------------------
    void update()
    {
        
    }
    
    
    //--------------------------------------------------------------
    void draw()
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        cam.begin();
        ofMatrix4x4 viewMatrix = ofGetCurrentViewMatrix();
        cam.end();
        
        PBRShader.begin();
        PBRShader.setUniformMatrix4f("projection", cam.getProjectionMatrix());
        PBRShader.setUniformMatrix4f("view", viewMatrix);
        
        PBRShader.setUniformTexture("albedoMap", albedo, 0);
        PBRShader.setUniformTexture("normalMap", normal, 1);
        PBRShader.setUniformTexture("metallicMap", metal, 2);
        PBRShader.setUniformTexture("roughnessMap", roughTex, 3);
        PBRShader.setUniformTexture("aoMap", aoTex, 4);
        
        PBRShader.setUniform3f("camPos", cam.getPosition());
        PBRShader.setUniform3f("lightPos", ofVec3f(10.0f, 10.0f, 10.0f));
        PBRShader.setUniform3f("lightColor", ofVec3f(1.0f, 1.0f, 1.0f));
        PBRShader.setUniform1f("exposure", 1.0f);
        
        
        for(int i = 0; i < NUM; i++)
        {
            ofMatrix4x4 model;
            model.scale(1.0f, 1.0f, 1.0f);
            model.translate(pos[i]);
            PBRShader.setUniformMatrix4f("model", model);
            sphere.draw();
        }
        
        
        
        //        {
        //            ofMatrix4x4 model;
        //            model.scale(1.0f, 1.0f, 1.0f);
        //            model.translate(10.0f, 10.0f, 10.0f);
        //            PBRShader.setUniformMatrix4f("model", model);
        //            lightSphere.draw();
        //        }
        
        
        
        
        PBRShader.end();
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
    settings.width = 980;
    settings.height = 520;
    settings.resizable = false;
    ofCreateWindow(settings);
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
}
