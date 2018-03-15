#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofBackground(239);
	ofSetWindowTitle("Insta");

	ofEnableDepthTest();
	this->font.loadFont("fonts/Kazesawa-Extrabold.ttf", 50, true, false, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	this->draw_water();
	this->draw_sand();
	for (int i = 0; i < 15; i++) {

		float param_1 = ofRandom(1000);
		float param_2 = ofRandom(0.005, 0.008);
		this->draw_fish(ofPoint(
			ofMap(ofNoise(param_1 * 0.1, ofGetFrameNum() * param_2), 0, 1, -ofGetWidth() / 2, ofGetWidth() /2),
			ofMap(ofNoise(param_1 * 0.3, ofGetFrameNum() * param_2), 0, 1, -ofGetHeight() / 2, ofGetHeight() / 2),
			ofMap(ofNoise(param_1 * 0.9, ofGetFrameNum() * param_2), 0, 1, 100, ofGetHeight() - 100)
		));
	}

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::draw_water() {

	ofSetColor(0, 0, 139);

	std::string words = "Water";
	ofPoint words_size = ofPoint(this->font.stringWidth(words), this->font.stringHeight(words));
	std::vector<ofTTFCharacter> paths = this->font.getStringAsPoints(words);

	for (int x = -ofGetWidth() / 2; x < ofGetWidth() / 2; x += words_size.x) {

		for (int y = -ofGetHeight() / 2; y < ofGetHeight() / 2; y += words_size.y) {

			ofPoint words_center(x + words_size.x / 2, y - words_size.y / 2);

			for (int p_index = 0; p_index < paths.size(); p_index++) {

				vector<ofPolyline> outline = paths[p_index].getOutline();

				std::vector<ofPoint> points;
				for (int o_index = 0; o_index < outline.size(); o_index++) {

					if (o_index > 0) {

						ofNextContour(true);
					}

					outline[o_index] = outline[o_index].getResampledBySpacing(1);
					vector<ofPoint> vertices = outline[o_index].getVertices();
					for (int v_index = 0; v_index < vertices.size(); v_index++) {

						ofPoint point = vertices[v_index] - words_center;
						float z = ofMap(ofNoise(point.x * 0.005, point.y * 0.005, ofGetFrameNum() * 0.005), 0, 1, 0, 80);
						points.push_back(point + ofPoint(0, 0, z));
					}
				}

				if (points.size() > 0) {

					ofBeginShape();
					ofVertices(points);
					ofEndShape(true);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_sand() {

	ofSetColor(39, 0, 0);

	std::string words = "Sand";
	ofPoint words_size = ofPoint(this->font.stringWidth(words), this->font.stringHeight(words));
	std::vector<ofTTFCharacter> paths = this->font.getStringAsPoints(words);

	for (int x = -ofGetWidth() / 2; x < ofGetWidth() / 2; x += words_size.x) {

		for (int y = -ofGetHeight() / 2; y < ofGetHeight() / 2; y += words_size.y) {

			ofPoint words_center(x + words_size.x / 2, y - words_size.y / 2);

			for (int p_index = 0; p_index < paths.size(); p_index++) {

				vector<ofPolyline> outline = paths[p_index].getOutline();

				std::vector<ofPoint> points;
				for (int o_index = 0; o_index < outline.size(); o_index++) {

					if (o_index > 0) {

						ofNextContour(true);
					}

					outline[o_index] = outline[o_index].getResampledBySpacing(1);
					vector<ofPoint> vertices = outline[o_index].getVertices();
					for (int v_index = 0; v_index < vertices.size(); v_index++) {

						ofPoint point = vertices[v_index] - words_center;
						float z = ofMap(ofNoise(point.x * 0.001, point.y * 0.001), 0, 1, 0, 80) + ofGetHeight();
						points.push_back(point + ofPoint(0, 0, z));
					}
				}

				if (points.size() > 0) {

					ofBeginShape();
					ofVertices(points);
					ofEndShape(true);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_fish(ofPoint location) {

	ofPushMatrix();
	ofTranslate(location);
	ofRotateX(90);

	std::string words = "Fish";
	ofPoint words_size = ofPoint(this->font.stringWidth(words), this->font.stringHeight(words));
	std::vector<ofTTFCharacter> paths = this->font.getStringAsPoints(words);

	ofColor fish_color;
	fish_color.setHsb(ofRandom(255), 239, 239);
	ofSetColor(fish_color);

	for (int p_index = 0; p_index < paths.size(); p_index++) {

		vector<ofPolyline> outline = paths[p_index].getOutline();

		std::vector<ofPoint> points;
		for (int o_index = 0; o_index < outline.size(); o_index++) {

			if (o_index > 0) {

				ofNextContour(true);
			}

			outline[o_index] = outline[o_index].getResampledBySpacing(1);
			vector<ofPoint> vertices = outline[o_index].getVertices();
			for (int v_index = 0; v_index < vertices.size(); v_index++) {

				points.push_back(vertices[v_index]);
			}
		}

		if (points.size() > 0) {

			ofBeginShape();
			ofVertices(points);
			ofEndShape(true);
		}
	}

	ofPopMatrix();
}

//========================================================================
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}