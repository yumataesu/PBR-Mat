#include "ofMain.h"


#define NUM 1

class ofApp : public ofBaseApp
{
    ofSpherePrimitive sphere, lightSphere, equireSphere;
    ofShader PBRShader;
    ofEasyCam cam;
    ofTexture albedo, normal, metal, aoTex, roughTex;
    ofTexture equire;
    
    ofVec3f pos[NUM];
    ofVec3f lightPos[5];
    
    //--------------------------------------------------------------
    void setup()
    {
        sphere.set(6.0f, 30.0f);
        lightSphere.set(5, 10);
        equireSphere.set(1000, 20);
        ofDisableArbTex();
        
        PBRShader.load("shaders/pbr");
        
        ofLoadImage(albedo, "textures/pbr/rusted_iron/albedo.png");
        ofLoadImage(normal, "textures/pbr/rusted_iron/normal.png");
        ofLoadImage(metal, "textures/pbr/rusted_iron/metallic.png");
        ofLoadImage(aoTex, "textures/pbr/rusted_iron/ao.png");
        ofLoadImage(roughTex, "textures/pbr/rusted_iron/roughness.png");
        ofLoadImage(equire, "textures/equire.jpg");
        
        
        glEnable(GL_DEPTH_TEST);
        
        float R = 50;
        for(int i = 0; i < 5; i++)
        {
            lightPos[i] = ofVec3f(ofRandom(-R, R), ofRandom(-R, R), ofRandom(-R, R));
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
        
        
        PBRShader.begin();
        PBRShader.setUniformMatrix4f("projection", cam.getProjectionMatrix());
        PBRShader.setUniformMatrix4f("view", viewMatrix);
        
        PBRShader.setUniformTexture("albedoMap", albedo, 0);
        PBRShader.setUniformTexture("normalMap", normal, 1);
        PBRShader.setUniformTexture("metallicMap", metal, 2);
        PBRShader.setUniformTexture("roughnessMap", roughTex, 3);
        PBRShader.setUniformTexture("aoMap", aoTex, 4);
        
        PBRShader.setUniform3f("camPos", cam.getPosition());
        for(int i = 0; i < 5; i++)
        {
            PBRShader.setUniform3f("light["+to_string(i)+"].position", lightPos[i]);
        }
        PBRShader.setUniform3f("lightColor", ofVec3f(1.0f, 1.0f, 1.0f));
        PBRShader.setUniform1f("exposure", 1.0f);
        
        
        for(int i = 0; i < NUM; i++)
        {
            ofMatrix4x4 model;
            model.scale(1.0f, 1.0f, 1.0f);
            model.translate(0.0, 0.0, 0.0);
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
    settings.width = 980;
    settings.height = 520;
    settings.resizable = false;
    ofCreateWindow(settings);
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
}
