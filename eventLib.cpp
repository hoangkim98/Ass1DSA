/*
 * =========================================================================================
 * Name        : eventLib.cpp
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 *               This library contains functions used for event management
 * =========================================================================================
 */

#include "eventLib.h"


/// NOTE: each event will be separated by spaces, or endline character
void loadEvents(char* fName, L1List<ninjaEvent_t> &eList) {
	fstream f;
	f.open(fName);
	string temp;
	while (getline(f, temp,'\n')){
		istringstream iss(temp);
		string data;
		while (iss>>data){
			if (data[data.size() - 1] == ';')
				data.erase(data.size() - 1, 1);
			ninjaEvent_t a(data);
			eList.push_back(a);
		}
	}
	f.close();
}
