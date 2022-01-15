#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetColor(255);

	this->font_size = 40;
	ofTrueTypeFontSettings font_settings("fonts/msgothic.ttc", this->font_size);
	this->font.load(font_settings);

	this->words = {

		"A", "B", "C", "D", "E",
		"F", "G", "H", "I", "J",
		"K", "L", "M", "N", "O",
		"P", "Q", "R", "S", "T",
		"U", "V", "W", "X", "Y", "Z",
	};

	for (int x = this->font_size * -15; x <= this->font_size * 15; x += this->font_size * 0.8) {

		for (int y = this->font_size * -15; y <= this->font_size * 15; y += this->font_size * 1.2) {

			this->location_list.push_back(glm::vec2(x - this->font_size * 0.2, y - this->font_size * 0.5));
			this->index_list.push_back(0.f);
			this->param_list.push_back(true);
		}
	}


}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	for (auto& param : this->param_list) {

		param = false;
	}

	for (int f = 0; f < 2; f++) {

		auto radius = ((ofGetFrameNum() * 10) + f * 500) % 1000;

		for (int i = 0; i < this->location_list.size(); i++) {

			if (glm::length(this->location_list[i]) > radius - 50 && glm::length(this->location_list[i]) < radius + 50) {

				this->index_list[i] += ofRandom(1, 5);

				this->index_list[i] = (int)this->index_list[i] % this->words.size();
				this->param_list[i] = true;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofTranslate(this->font_size * 0.5, this->font_size * 0.5);

	for (int i = 0; i < this->location_list.size(); i++) {

		ofPushMatrix();
		ofTranslate(this->location_list[i]);

		if (this->param_list[i]) {

			ofRotateY(ofMap(ofNoise(this->location_list[i].y * 0.005, ofGetFrameNum() * 0.01), 0, 1, -360, 360));
			ofRotateX(ofMap(ofNoise(this->location_list[i].x * 0.005, ofGetFrameNum() * 0.01), 0, 1, -360, 360));
		}

		this->font.drawString(this->words[this->index_list[i]], this->font_size * -0.5, this->font_size * -0.5);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}