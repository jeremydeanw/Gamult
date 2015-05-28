#include "ofApp.h"

Module::Module(int index, float x, float y, float width, float height, int maxPopulation, vector<string> soundPaths, vector<string> iconPaths) {

	this->index = index;
	this->x0 = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->maxPopulation = maxPopulation;

	this->console = new ModuleConsole(x0, width, index, iconPaths);
	
	this->x1 = x + width;
	
	loadSounds(soundPaths);

}

void Module::loadSounds(vector<string> paths) {
    for (int i = 0; i < paths.size(); i++) {
        ofSoundPlayer s;
        sounds.push_back(s);
        sounds[i].setMultiPlay(true);
        sounds[i].loadSound(paths[i], true);
    }
}

void Module::changeInstrument(int index) {
	cout << "changing isntrument" << endl;
}

void Module::addParticle(int life, int x, int y) {
	if (particles.size() < maxPopulation) {
        if (x >= x0 && x <= x1 && y >= CONSOLE_HEIGHT) {
            // the following line is to make sure that when the particle is created it always goes downwards first (was causing problems with Particle::gravity(); 
            if (y <= CONSOLE_HEIGHT + life) y = CONSOLE_HEIGHT + life + 1;
			particles.push_back(Particle(index, particles.size(), x, y, life));
		}
	}
}

void Module::update() {
	for (int i = 0; i < particles.size(); i++) {
		Particle *p = &particles[i];
		if (!isFreezed() && isLooping()) p->loop();
		if (!isFreezed() && isGravityOn()) {
			if (p->getCounter() >= p->getLife()) particles.erase(particles.begin()+i);
			else p->gravity();
		}
	}
}

void Module::draw() {
	console->draw();
//    panel->draw();
	drawBorders();
	drawGrid();
	drawParticles();
}

void Module::drawParticles() {
	for (int i = 0; i < particles.size(); i++)
		particles[i].draw();
}

void Module::drawGrid() {
	ofSetColor(GRID_COLOR);
	int gridNumberElements = sounds.size();
	int gridCellSize = round(float(width) / gridNumberElements);
	for (int i = 1; i < gridNumberElements; i++) {
		int gridCellX = x0 + (i)*gridCellSize;
//    	ofLine(gridCellX, ofGetHeight(), gridCellX, ofGetHeight()-GRID_HEIGHT); // small grids at bottom
    	ofLine(gridCellX, ofGetHeight(), gridCellX, CONSOLE_HEIGHT); // top to bottom grids
	}
}

void Module::drawBorders() {
	ofPushStyle();
	ofSetLineWidth(CONSOLE_BORDER_WIDTH);
	ofSetHexColor(CONSOLE_BORDER_COLOR);
	ofNoFill();
	ofRect(x0, y, width, ofGetHeight());
	ofPopStyle();
}

void Module::playSound(int index, float vol) {
    sounds[index].setVolume(vol);
    sounds[index].play();
}
