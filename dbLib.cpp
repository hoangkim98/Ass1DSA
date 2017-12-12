/*
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 *               This file implements functions used for database management
 * =========================================================================================
 */

#include "dbLib.h"

#include <time.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <ctime>
#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

using namespace std;


void    strPrintTime(char* des, time_t& t) {
    tm *pTime = localtime(&t);
    strftime(des, 26, "%Y-%m-%d %H:%M:%S", pTime);
}

//void loadNinjaDB(char* fName, L1List<NinjaInfo_t> &db) {
//	int count;
//	ifstream f;
//	string temp, temp2;
//	NinjaInfo_t read;
//	f.open(fName, ios::in);
//	istringstream iss;
//	getline(f, temp);
//	while(getline(f,temp)){
//		string zero = "0";
//		if (temp == "")continue;
//		iss.str(temp);
//		getline(iss, temp, ',');
//		getline(iss, temp, ',');
//		tm tm{};
//		istringstream iss2(temp);
//		iss2 >> get_time(&tm, "%m/%d/%Y %T");
//		read.timestamp = mktime(&tm);
//		getline(iss, temp, ',');
//		if (temp.length() < 4) {
//			count = 4 - temp.length();
//			for (int lz = 0; lz < count - 1; lz++)	zero += zero;
//			zero += temp;
//			temp = zero;
//		}
//		strcpy(read.id, temp.c_str());
//		getline(iss, temp, ',');
//		read.longitude = atof(temp.c_str());
//		getline(iss, temp, ',');
//		read.latitude = atof(temp.c_str());
//		iss.clear();
//		db.push_back(read);
//	}
//	f.close();
//}
void loadNinjaDB(char* fName, L1List<NinjaInfo_t> &db) {
	int count;
	ifstream f;
	string temp, temp2;
	NinjaInfo_t read;
	f.open(fName, ios::in);
	istringstream iss;
	getline(f, temp);
	while (!f.eof()) {
		string zero = "0";
		getline(f, temp);
		if (temp == "")continue;
		iss.str(temp);
		getline(iss, temp, ',');
		getline(iss, temp, ',');
		tm tm{};
		istringstream iss2(temp);

	/*	getline(iss2, temp, '/');
		tm.tm_mon = atoi(temp.c_str());
		getline(iss2, temp, '/');
		tm.tm_mday = atoi(temp.c_str()) - 1;
		getline(iss2, temp, ' ');
		tm.tm_year = atoi(temp.c_str()) - 1900;
		getline(iss2, temp, ':');
		tm.tm_hour = atoi(temp.c_str());
		getline(iss2, temp, ':');
		tm.tm_min = atoi(temp.c_str());
		iss2 >> temp;
		tm.tm_sec = atoi(temp.c_str());*/

		tm.tm_mon = stoi(temp.substr(0, 2)) - 1;
		tm.tm_mday = stoi(temp.substr(3, 2));	
		tm.tm_year = stoi(temp.substr(6, 4)) - 1900;
		tm.tm_hour = stoi(temp.substr(11, 2));
		tm.tm_min = stoi(temp.substr(14, 2));
		tm.tm_sec = stoi(temp.substr(17, 2));

		/*char *charTime = new char(22);
		strncpy(charTime, temp.c_str(), 22);
		strptime(charTime, "%m%d/%Y %T", &tm);*/

		read.timestamp = mktime(&tm);
		getline(iss, temp, ',');
		if (temp.length() < 4) {
			count = 4 - temp.length();
			for (int lz = 0; lz < count - 1; lz++)	zero += zero;
			zero += temp;
			temp = zero;
		}
		strcpy(read.id, temp.c_str());
		getline(iss, temp, ',');
		read.longitude = atof(temp.c_str());
		getline(iss, temp, ',');
		read.latitude = atof(temp.c_str());
		iss.clear(); iss2.clear();
		db.push_back(read);
	}
	f.close();
}

//void loadNinjaDB(char* fName, L1List<NinjaInfo_t> &db) {
//
//	ifstream infile(fName);
//	string data, temp;
//	stringstream fss, iss;
//	fss << infile.rdbuf();
//	infile.close();
//	getline(fss, data, '\n');
//	iss.str(data);
//	int i = -1, a[4] = {};
//	while (getline(iss, temp, ',')) {
//		i++;
//		if (temp == "REPORT_TIME") a[0] = i;
//		else if (temp == "NINJA_TAG") a[1] = i;
//		else if (temp == "LONGITUDE") a[2] = i;
//		else if (temp == "LATITUDE") a[3] = i;
//	}
//	string b[50];
//	while (getline(fss, data, '\n')) {
//		if (data == "") continue;
//		iss.clear(); iss.str(data);
//		for (int i = 0; getline(iss, temp, ','); i++) b[i] = temp;
//		NinjaInfo_t tail;
//		strcpy(tail.id, b[a[1]].c_str());
//		tail.latitude = atof(b[a[3]].c_str());
//		tail.longitude = atof(b[a[2]].c_str());
//		tm tm{};
//		stringstream iss(b[a[0]]);
//		iss >> get_time(&tm, "%d/%m/%Y %T");
//		tail.timestamp = mktime(&tm);
//		db.push_back(tail);
//	}
//}

bool parseNinjaInfo(char* pBuf, NinjaInfo_t& nInfo) {
    // TODO: write code to parse information from a string buffer, ignore if you don't use it
    return true;
}


void process(L1List<ninjaEvent_t>& eventList, L1List<NinjaInfo_t>& bList) {
	void*   pGData = NULL;
	ninjaEvent_t arr[100], a[100];
	int i = 0;
	L1Item<ninjaEvent_t>* temp = eventList._pHead;
	while (temp) {
		arr[i] = temp->data;
		temp = temp->pNext;
		i++;
	}
	sprintf(a[0].code, "%d", i);
	for (int j = 1; j <= i; j++) a[j] = arr[j - 1];
	pGData = a;
    while (!eventList.isEmpty()) {
        if(!processEvent(eventList[0], bList, pGData))
            cout << eventList[0].code << " is an invalid event\n";
		    eventList.removeHead();
    }
}

bool initNinjaGlobalData(void** pGData) {
	return true;
}

void releaseNinjaGlobalData(void* pGData) {
	/// TODO: You should define this function if you allocated extra data at initialization stage
	/// The data pointed by pGData should be released
	return;
}

void printNinjaInfo(NinjaInfo_t& b) {
    printf("%s: (%0.5f, %0.5f), %s\n", b.id, b.longitude, b.latitude, ctime(&b.timestamp));
}

/// This function converts decimal degrees to radians
double deg2rad(double deg) {
    return (deg * pi / 180);
}

///  This function converts radians to decimal degrees
double rad2deg(double rad) {
    return (rad * 180 / pi);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = deg2rad(lat1d);
    lon1r = deg2rad(lon1d);
    lat2r = deg2rad(lat2d);
    lon2r = deg2rad(lon2d);
    u = sin((lat2r - lat1r)/2);
    v = sin((lon2r - lon1r)/2);
    return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}