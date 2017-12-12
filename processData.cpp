/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : student code for Assignment 1 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */
#include "eventLib.h"
#include "dbLib.h"
typedef struct save {
	double _result;
	char ID[7];
}save;
bool Event0(void* pGData,char code[20]){
	ninjaEvent_t* nPointer = (ninjaEvent_t*)pGData;
	int count = atoi(nPointer[0].code);
	cout << code << ":";
	for (int i = 1; i <= count; i++)cout << " " << nPointer[i].code;
	cout << endl;
	return true;
}
bool Event1(L1List<NinjaInfo_t> nList,char* result) {
	cout << 1 << ": ";
	if (nList._pHead == NULL) {
		cout << "empty" << endl;
		return true;
	}
	cout << result << endl;
	return true;
}
bool Event2(L1List<NinjaInfo_t> nList,char* result) {
	cout << 2 << ": ";
	if (nList._pHead == NULL) {
		cout << "empty" << endl;
		return true;
	}
	cout << result << endl;
	return true;
}
bool Event3(L1List<NinjaInfo_t> nList) {
	cout << 3 << ": ";
	if (nList._pHead == NULL) {
		cout << 0 << endl;
		return true;
	}
	int count = 1;
	L1Item<NinjaInfo_t>*temp = nList._pHead;
	char id[10] = "";
	strcpy(id, temp->data.id);
	while (temp) {
		if (strcmp(id, temp->data.id) != 0) {
			count++;
			strcpy(id, temp->data.id);
		}
		temp = temp->pNext;
	}
	cout<< count << endl;
	return true;
}
bool Event4(L1List<NinjaInfo_t> nList) {
	cout << 4 << ": ";
	if (nList._pHead == NULL) {
		cout << "empty" << endl;
		return true;
	}
	L1Item<NinjaInfo_t> *temp = nList._pHead;
	char *temp2 = temp->data.id;
	while (temp) {
		if (strcmp(temp->data.id, temp2) > 0)temp2 = temp->data.id;
		temp = temp->pNext;
	}
	cout<< temp2 << endl;
	return true;
}
bool Event5(L1List<NinjaInfo_t> nList, bool check, L1Item<NinjaInfo_t>*head, string foundedID) {
	char x[30];
	cout << 5 << foundedID << ": ";
	if (check == false) {
		cout << -1 << endl;
		return true;
	}
	L1Item<NinjaInfo_t>*temp1 = head, *temp2 = temp1->pNext;
	if (temp2 == NULL) {
		strPrintTime(x, temp1->data.timestamp);
		puts(x);
		return true;
	}
	while (temp2) {
		if (strcmp(foundedID.c_str(), temp2->data.id) != 0) break;
		else if (distanceEarth(temp2->data.latitude, temp2->data.longitude,
			temp1->data.latitude, temp1->data.longitude) * 1000 > 5) {
			if (temp2 == temp1->pNext) {
				strPrintTime(x, temp1->data.timestamp);
				puts(x);
				return true;
			}
			else {
				strPrintTime(x, temp2->data.timestamp);
				puts(x);
				return true;
			}
		}
		temp2 = temp2->pNext;
	}
	cout << "empty" << endl;
	return true;
}
bool Event6(L1List<NinjaInfo_t> nList, bool check, L1Item<NinjaInfo_t>*head, string foundedID) {
	char x[30];
	cout << 6 << foundedID << ": ";
	if (check == false) {
		cout << -1 << endl;
		return true;
	}
	double a, b;
	L1Item<NinjaInfo_t>*temp1 = head, *stopPoint = NULL, *movePoint=head, *temp2 = temp1->pNext;
	// 1 node
	if (temp2 == NULL || strcmp(temp1->data.id, temp2->data.id) != 0) {
		cout << "Non-stop1" << endl;
		return true;
	}
	// 2 nodes
	else if (temp2->pNext == NULL || strcmp(temp2->pNext->data.id, temp1->data.id) != 0) {
		a = distanceEarth(temp1->data.latitude, temp1->data.longitude, temp2->data.latitude, temp2->data.longitude);
		if (a > 0.005) {
			cout << "Non-stop2" << endl;
			return true;
		}
		else {
			strPrintTime(x, temp2->data.timestamp);
			puts(x);
			return true;
		}
	}
	// >2 nodes
	else {
		bool check = false;
		while (temp2->pNext) {
			if (strcmp(temp2->data.id, temp1->data.id) != 0)break;
			a = distanceEarth(temp1->data.latitude, temp1->data.longitude, temp2->data.latitude, temp2->data.longitude);
			b = distanceEarth(temp2->data.latitude, temp2->data.longitude, temp2->pNext->data.latitude, temp2->pNext->data.longitude);
			if (a > 0.005) {
				temp1 = temp2;	
				if (b <= 0.005)stopPoint = temp2;
				check = true;
			} 
			else movePoint = temp2;
			temp2 = temp2->pNext;
		}
		if (stopPoint == NULL) {
			strPrintTime(x, head->data.timestamp);
			puts(x);
			return true;
		}
		if (movePoint == head) {
			cout << "Non-stop" << endl;
			return true;
		}
		else {
			strPrintTime(x, stopPoint->data.timestamp);
			puts(x);
			return true;
		}
	}
}
bool Event7(L1List<NinjaInfo_t> nList, bool check, L1Item<NinjaInfo_t>*head, string foundedID) {
	bool checkstop = false;
	int count = 0;
	cout << 7 << foundedID << ": ";
	if (check == false) {
		cout << -1 << endl;
		return true;
	}
	L1Item<NinjaInfo_t>*temp1 = head, *temp2 = temp1->pNext;
	while (temp2) {
		if (strcmp(temp2->data.id, foundedID.c_str()) != 0) break;
		if (distanceEarth(temp1->data.latitude, temp1->data.longitude, temp2->data.latitude, temp2->data.longitude) * 1000 > 5) {
			if (checkstop) {
				count++;
				checkstop = false;
			}
			temp1 = temp2;
		}
		else checkstop = true;
		temp2 = temp2->pNext;
	}
	if (checkstop)count++;
	cout << count << endl;
	return true;
}
bool Event8(L1List<NinjaInfo_t> nList, bool check, L1Item<NinjaInfo_t>*head, string foundedID) {
	double distance = 0, a;
	cout << 8 << foundedID << ": ";
	if (check == false) {
		cout << -1 << endl;
		return true;
	}
	L1Item<NinjaInfo_t>*temp1 = head, *temp2 = temp1->pNext;
	while (temp2) {
		if (strcmp(temp2->data.id, foundedID.c_str()) != 0)break;
		a = distanceEarth(temp1->data.latitude, temp1->data.longitude, temp2->data.latitude, temp2->data.longitude);
		distance += a;
		temp1 = temp2;
		temp2 = temp1->pNext;
	}
	cout << distance << endl;
	return true;
}
bool Event9(L1List<NinjaInfo_t> nList) {
	cout << 9 << ": ";
	if (nList._pHead == NULL) {
		cout << -1 << endl;
		return true;
	}
	save arr[500];
	char id[10];
	strcpy(id, nList._pHead->data.id);
	L1Item<NinjaInfo_t>*temp1 = nList._pHead, *temp2 = temp1->pNext;
	int count = 0;
	double distance = 0, a;
	if (temp2 == NULL) {
		cout << temp1->data.id << endl;
		return true;
	}
	while (temp2) {
		a = distanceEarth(temp1->data.latitude, temp1->data.longitude, temp2->data.latitude, temp2->data.longitude);
		distance += a;
		temp1 = temp2;
		temp2 = temp1->pNext;
		if (strcmp(temp2->data.id, id) != 0 || temp2->pNext == NULL) {
			if (temp2->pNext == NULL) {
				a = distanceEarth(temp1->data.latitude, temp1->data.longitude, temp2->data.latitude, temp2->data.longitude);
				distance += a;
			}
			strcpy(arr[count].ID, temp1->data.id);
			arr[count]._result = distance;
			distance = 0;
			count++;
			if (temp2->pNext)strcpy(id, temp2->data.id);
			temp1 = temp2;
			temp2 = temp1->pNext;
		}
	}
	save max = arr[0];
	for (int k = 0; k <= count; k++)if (arr[k]._result > max._result)max = arr[k];
	cout<< max.ID << endl;
	return true;
}
bool Event10(L1List<NinjaInfo_t> nList) {
	cout << 10 << ": ";
	if (nList._pHead == NULL) {
		cout << -1 << endl;
		return true;
	}
	save arr[500];
	char id[10];
	strcpy(id, nList._pHead->data.id);
	L1Item<NinjaInfo_t>*temp1 = nList._pHead, *temp2 = temp1->pNext;
	int result = 0, count = 0;
	if (temp2 == NULL) {
		cout << temp1->data.id << endl;
		return true;
	}
	while (temp2) {
		if (distanceEarth(temp1->data.latitude, temp1->data.longitude, temp2->data.latitude, temp2->data.longitude) > 0.005)
			result += temp2->data.timestamp - temp1->data.timestamp;
		temp1 = temp2;
		temp2 = temp1->pNext;
		if (strcmp(temp2->data.id, id) != 0 || temp2->pNext == NULL) {
			strcpy(arr[count].ID, temp1->data.id);
			arr[count]._result = result;
			result = 0;
			count++;
			if (temp2->pNext)strcpy(id, temp2->data.id);
			temp1 = temp2;
			temp2 = temp1->pNext;
		}
	}
	save max = arr[0];
	for (int k = 0; k <= count; k++)if (arr[k]._result > max._result)max = arr[k];
	cout<< max.ID << endl;
	return true;
}
bool Event11(L1List<NinjaInfo_t>& nList, string tempE11) {
	cout << 11 << tempE11 << ": ";
	L1Item<NinjaInfo>* temp = nList._pHead;
	char Max[5] = "";
	while (temp) {
		if (strcmp(temp->data.id, tempE11.c_str()) < 0) {
			strcpy(Max, temp->data.id);
			break;
		}
		temp = temp->pNext;
	}
	if (strcmp(Max, "") == 0) {
		cout << -1 << endl;
		return true;
	}
	else {
		temp = nList._pHead;
		while (temp) {
			if (strcmp(temp->data.id, tempE11.c_str()) < 0 && strcmp(temp->data.id, Max) > 0)
				strcpy(Max, temp->data.id);
			temp = temp->pNext;
		}
		temp = nList._pHead;
		while (temp && temp->pNext) {
			while (temp->pNext && temp->pNext->data == Max) {
				L1Item<NinjaInfo>* p = temp->pNext;
				temp->pNext = temp->pNext->pNext;
				delete p;
				nList._size--;
			}
			temp = temp->pNext;
		}
		if (strcmp(nList._pHead->data.id, Max) == 0)
			nList.removeHead();
		cout << Max << endl;
		return true;
	}
	
}
bool Event12(L1List<NinjaInfo_t> nList) {
	cout << 12 << ": ";
	if (nList._pHead == NULL) {
		cout << -1 << endl;
		return true;
	}
	save arr[500];
	char id[10];
	strcpy(id, nList._pHead->data.id);
	L1Item<NinjaInfo_t>*temp1 = nList._pHead, *temp2 = temp1->pNext;
	int result = 0, count = 0;
	while (temp2) {
		if (distanceEarth(temp1->data.latitude, temp1->data.longitude,
			temp2->data.latitude, temp2->data.longitude) <= 0.005)
			result += temp2->data.timestamp - temp1->data.timestamp;
		temp1 = temp2;
		temp2 = temp2->pNext;
		if (strcmp(temp2->data.id, id) != 0 || temp2->pNext == NULL) {
			strcpy(arr[count].ID, temp1->data.id);
			arr[count]._result = result;
			result = 0;
			count++;
			if (temp2->pNext)strcpy(id, temp2->data.id);
			temp1 = temp2;
			temp2 = temp1->pNext;
		}
	}
	save max = arr[0];
	for (int k = 0; k <= count; k++)if (arr[k]._result > max._result)max = arr[k];
	cout << max.ID << endl;
	return true;
}
bool Event13(L1List<NinjaInfo_t> nList) {
	return true;
}
bool Event14(L1List<NinjaInfo_t>nList) {
	cout << 14 << ":";
	if (nList._pHead == NULL) {
		cout << " -1" << endl;
		return true;
	}
	bool checkIfSuitable = false;
	L1Item<NinjaInfo_t>*temp1 = nList._pHead, *temp2 = temp1->pNext;
	L1List<NinjaInfo_t>checkpoint;
	checkpoint.push_back(temp1->data);
	L1Item<NinjaInfo_t>*headCheck = checkpoint._pHead;
	bool gotOne = false; //jump to next ninja 
	double a, b;
	while (temp2) {
		if (gotOne) {
			while (temp2) {
				if (strcmp(temp2->data.id, temp1->data.id) != 0) {
					temp1 = temp2;
					temp2 = temp1->pNext;
					checkpoint.destroyList();
					checkpoint.push_back(temp1->data);
					headCheck = checkpoint._pHead;
					break;
				}
				temp2 = temp2->pNext;
			}
			gotOne = false;
		}
		if (temp2 == NULL)break;
		a = distanceEarth(temp1->data.latitude, temp1->data.longitude,
			temp2->data.latitude, temp2->data.longitude);
		if (a > 0.005) {
			temp1 = temp2;
			while (headCheck) {
				b = distanceEarth(temp2->data.latitude, temp2->data.longitude,
					headCheck->data.latitude, headCheck->data.longitude);
				if ( b<= 0.005) {
					cout << " " << headCheck->data.id;
					checkIfSuitable = true;
					gotOne = true;	
					break;
				}
				headCheck = headCheck->pNext;
			}
			checkpoint.push_back(temp2->data);
			headCheck = checkpoint._pHead;
		}
		temp2 = temp2->pNext;
		// if find next ninja
		if (strcmp(temp1->data.id, temp2->data.id) != 0) {
			temp1 = temp2;
			temp2 = temp1->pNext;
			checkpoint.destroyList();
			checkpoint.push_back(temp1->data);
			headCheck = checkpoint._pHead;
		}
	}
	if (checkIfSuitable == false) {
		cout << " -1" << endl;
		return true;
	}
	cout << endl;
	return true;
}
bool processEvent(ninjaEvent_t& event, L1List<NinjaInfo_t>& nList, void* pGData) {
	char result1[10], result2[10];
	if (nList._pHead) {
		strcpy(result1, nList._pHead->data.id);
		strcpy(result2, nList.pTail->data.id);
	}
	if (event.code[0] == '0')return Event0(pGData, event.code);
	if (event.code[0] == '1' && event.code[1] == '\0')return Event1(nList, result1);
	if (event.code[0] == '2' && event.code[1] == '\0')return Event2(nList, result2);
	if (event.code[0] == '3' && event.code[1] == '\0')return Event3(nList);
	if (event.code[0] == '4' && event.code[1] == '\0')return Event4(nList);
	if (event.code[0] == '9' && event.code[1] == '\0')return Event9(nList);
	if (event.code[0] == '1' && event.code[1] == '0'&&event.code[2] == '\0')return Event10(nList);
	if (event.code[0] == '1' && event.code[1] == '2'&&event.code[2] == '\0')return Event12(nList);
	if (event.code[0] == '1' && event.code[1] == '4'&&event.code[2] == '\0')return Event14(nList);
	if (string(event.code).length() > 1) {
		if (event.code[0] == '5' || event.code[0] == '6' ||
			event.code[0] == '7' || event.code[0] == '8') {
			char foundedID[22] = "";
			strcpy(foundedID, &event.code[1]);
			L1Item<NinjaInfo_t>*temp = nList._pHead;
			bool check = false;
			while (temp) {
				if (strcmp(nList._pHead->data.id, foundedID) == 0 ||
					strcmp(temp->data.id, foundedID) == 0) {
					check = true;
					break;
				}
				temp = temp->pNext;
			}
			if (event.code[0] == '5')return Event5(nList, check, temp, foundedID);
			if (event.code[0] == '6')return Event6(nList, check, temp, foundedID);
			if (event.code[0] == '7')return Event7(nList, check, temp, foundedID);
			if (event.code[0] == '8')return Event8(nList, check, temp, foundedID);
		}
		else
			if (string(event.code).length() > 2) {
				if (event.code[0] == '1') {
					char foundedID[22] = "";
					strcpy(foundedID, &event.code[2]);
					if (event.code[1] == '1')return Event11(nList, foundedID);
					if (event.code[1] == '3')return Event13(nList);
				}
			}
	}
	return false;
}

