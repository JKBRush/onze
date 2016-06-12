#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();
        bool coordinate;
		void mouseDragged(int x, int y, int button);
    
};
