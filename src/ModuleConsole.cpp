#include "ofApp.h"
#include "Button.h"

ModuleConsole::ModuleConsole(int x, float width, int module, vector<string> iconPaths) {
	
	this->width = width;
	this->x = x;
	this->y = 0;
	this->module = module;
	
	int y = 0;
    
    int buttonSize = ofGetHeight()*0.018;
	
	remove = new Button(BUTTON_CLICK,  module, buttonSize, x+buttonSize, y+buttonSize,   "Remove");
	loop =   new Button(BUTTON_TOGGLE, module, buttonSize, x+buttonSize, y+buttonSize*3, "Loop");
	freeze = new Button(BUTTON_TOGGLE, module, buttonSize, x+buttonSize, y+buttonSize*5, "Freeze");

	x = x + width/2;
	gravity   = new Fader(x, y+10+5, FADER_SIZE, FADER_RANGE, "Gravity");
	loopSpeed = new Fader(x, y+50+5, FADER_SIZE, FADER_RANGE, "Loop Speed");
	
	loadIcons(iconPaths);
	
	ofAddListener(ofEvents().mouseReleased, this, &ModuleConsole::mousePressed);
	
}

void ModuleConsole::loadIcons(vector<string> paths) {
	for (int i = 0; i < paths.size(); i++) {
		ofImage img;
		img.loadImage(paths[i]);
		icons.push_back(img);
	
		// TODO: extrapolate to proper globals or constants
    	int padding = 5;
    	int size = 20;
        int buttonSize = ofGetHeight()*0.018;
    	int y = CONSOLE_HEIGHT - size - padding;
		
		ofRectangle rect;
		rect.set(x+buttonSize + i*size, y, size, size);
		rects.push_back(rect);
	}
	
}

void ModuleConsole::draw() {

	ofPushStyle();
	
	ofSetHexColor(CONSOLE_COLOR);

	ofFill();

	ofRect(x, y, width, CONSOLE_HEIGHT);

	ofPopStyle();

	remove->draw();
	loop->draw();
	freeze->draw();

	gravity->draw();
	loopSpeed->draw();
	
	drawIcons();

}

void ModuleConsole::drawIcons() {
	// TODO: extrapolate to proper globals or constants
	int padding = 5;
	int size = 20;
    int buttonSize = ofGetHeight()*0.018;
	int y = CONSOLE_HEIGHT - size - padding;
	for (int i = 0; i < icons.size(); i++) {
		icons[i].draw(x+buttonSize + i*size, y, size, size);
//		ofRect(rects[i]);
	}
	
}

void ModuleConsole::mousePressed(ofMouseEventArgs& event) {
	for (int i = 0; i < rects.size(); i++) {
		if (rects[i].inside(event.x, event.y)) {
			cout << "module " << module << " active instrument now is index " << i << endl;
			ofApp::modules[module]->changeInstrument(i);
			return;
		}
	}
}

bool ModuleConsole::isFreezed() {
	return freeze->getState();
}

bool ModuleConsole::isLooping() {
	return loop->getState();
}
