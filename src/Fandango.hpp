class Fandango{
private:
    ofxTrueTypeFontUC font;
    vector<string> circleStr;
    vector<float> circlePi;
    float depth;
    float rad;
    
public:
    static int interval;
    
    void setup(vector<string> _sentence, float _radius, int _interval) {
        font.loadFont("Ag.ttf", 20, true, true);
        rad = _radius;
        interval = _interval;
        
        for(int i = 0; i < _sentence.size(); i++){
            float pi = ofMap(i, 0, _sentence.size(), 0, PI*2);
            circlePi.push_back(pi);
            
            circleStr.push_back(_sentence[i]);
        }
    }
    
    void update(float _speed) {
        depth -= _speed;
        if(depth < -2000){
            depth = -500;
        }
    }
    
    void draw() {
        ofTranslate(0, 0, interval);
        for (int i = 0; i < circlePi.size(); i++) {
            float pi = ofMap(i, 0, circlePi.size(), 0, PI*2);
            ofPushMatrix();
            circlePi[i]-=0.01;
            ofTranslate(rad*sin(circlePi[i]), rad*cos(circlePi[i]), depth);
            font.drawString(circleStr[i], 0, 0);
            ofPopMatrix();
        }
    }
};

int Fandango::interval;


