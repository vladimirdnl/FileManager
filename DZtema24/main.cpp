#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdio.h>
#include <windows.h>
using namespace std;
//���������
void showmenu();
char* pathToFind(char *path);
char* enterFolder(char *path, char *foldername);
char* scannerf(char *command);
char* doFunct(WIN32_FIND_DATA &FindFileData, HANDLE &hf, char* flag, char *command, char *pathor);
char* scannern(char *command);
char* scannerp(char *command);
char* readNameToReal(char *name, char *pathor);
int showfiles(WIN32_FIND_DATA &FindFileData, HANDLE &hf, char *pathToFind);
int testfiles(WIN32_FIND_DATA &FindFileData, HANDLE &hf, char *pathToFind);
//
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	char* path = new char[256]{};
	char* pathFind;
	char* crFilNme = new char[256]{};
	showmenu();
	while (true) {
		cout << "������� ��������� ����(������� \\ ����� ������������)" << endl;
		cin.getline(path, 256);
		pathFind = pathToFind(path);
		if (showfiles(FindFileData, hf, pathFind) != 0) break;
		else {
			system("cls");
			cout << "����������� ������ ����" << endl; 
			system("pause");
			system("cls");
		}
	}

	while (true) {
		char *input = new char[256]{};
		cin.getline(input, 256);
		char* flag = scannerf(input);
		if (flag != nullptr) {
			if (flag[0] == 'e' && flag[1] == 'x' && flag[2] == 't') return 0;
			if (flag[0] == 'h' && flag[1] == 'l' && flag[2] == 'p') showmenu();
			path = doFunct(FindFileData, hf, flag, input, path);
			pathFind = pathToFind(path);
		}
		system("cls");
		if (showfiles(FindFileData, hf, pathFind) == 0) {
			cout << "������������ ����, ��������� ������� ����:" << endl;

		}
	}
	FindClose(hf);
	system("pause");
	return 0;
}
//�������
char* scannerp(char *command) {
	//��������� ����, ������� ��������� ����� �����
	char *path;
	int comsize = 0, pathsize = 0, kpath = 0, dot = 0;
	for (int i = 0; command[i] != '\0'; i++) comsize++;
	for (int i = 0; i < comsize; i++) {
		if (dot == 3) {
			pathsize++;
		}
		if (command[i] == '.') dot++;
	}
	path = new char[pathsize + 1]{};
	dot = 0;
	for (int i = 0; i < comsize; i++) {
		if (dot == 3) {
			path[kpath] = command[i];
			kpath++;
		}
		if (command[i] == '.') dot++;
	}
	return path;
}
char* scannern(char *command) {
	//��������� ���, ������� ���������� ����� �����
	char *name;
	int comsize = 0, namesize = 0, kname = 0, dot = 0;
	for (int i = 0; command[i] != '\0'; i++) comsize++;
	for (int i = 0; i < comsize; i++) {
		if (dot == 1 || dot == 2) {
			namesize++;
		}
		if (command[i] == '.') dot++;

	}
	name = new char[namesize + 1]{};
	dot = 0;
	for (int i = 0; i < comsize; i++) {
		if (dot == 1 || dot == 2) {
			name[kname] = command[i];
			kname++;
		}
		if (command[i] == '.') dot++;

	}
	return name;
}
char* readNameToReal(char *name, char *pathor) {
	//����� ������ ������� ����
	char *readname;
	int namesize = 0, sizepath = 0, sizern;
	for (int i = 0; name[i] != '\0'; i++) namesize++;
	for (int i = 0; pathor[i] != '\0'; i++) sizepath++;
	sizern = namesize + sizepath + 1;
	readname = new char[sizern] {};
	for (int i = 0; i < sizern - 1; i++) {
		if (i < sizepath) {
			readname[i] = pathor[i];
		}
		else {
			readname[i] = name[i - sizepath];
		}
	}
	return readname;
}
//�� ��������� ������ �� �������� � �������, ������� � � path ������ ��������� ��� �������� �� �������
char* doFunct(WIN32_FIND_DATA &FindFileData, HANDLE &hf, char* flag, char *command, char *pathor) {
	char *name;
	char *path;
	//delete
	if (flag[0] == 'd' && flag[1] == 'l' && flag[2] == 't') {
		name = scannern(command);
		name = readNameToReal(name, pathor);
		bool h;
		if (!(h = DeleteFile(name))) cout << "�� ������� ������� ����" << endl;
		else cout << "���� ������� �����!" << endl;
	}
	//copy
	else if (flag[0] == 'c' && flag[1] == 'p' && flag[2] == 'y') {
		char *pathname, pathsize = 0, pathnamesize;
		name = scannern(command);
		int sizename = 0;
		for (int i = 0; name[i] != '\0'; i++) sizename++;
		name[sizename - 1] = '\0';
		path = scannerp(command);
		for (int i = 0; path[i] != '\0'; i++)pathsize++;
		pathnamesize = pathsize + sizename + 1;
		pathname = new char[pathnamesize] {};
		for (int i = 0; i < pathnamesize - 1; i++) {
			if (i < pathsize) {
				pathname[i] = path[i];
			}
			else pathname[i] = name[i - pathsize];
		}
		name = readNameToReal(name, pathor);
		bool h;
		if (!(h = CopyFile(name, pathname, true))) cout << "�� ������� ���������� ����" << endl;
		else cout << "���� ������� ����������!" << endl;
	}
	//create
	else if (flag[0] == 'c' && flag[1] == 'r' && flag[2] == 't') {
		name = scannern(command);
		name = readNameToReal(name, pathor);
		HANDLE h;
		if ((h = CreateFile(name, GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE) cout << "�� ������� ������� ����" << endl;
		else cout << "���� ������� ������!" << endl;
	}
	//rename
	else if (flag[0] == 'r' && flag[1] == 'n' && flag[2] == 'm') {
		//����� �� �������� ������ ����� �����    ��� � �����������
		char *newname, *ext, *newfilename;//ext - ����������
		int namesize = 0, sizenew = 0, sizenewfilename = 0, extsize = 0, kext = 0, dot = 0;
		name = scannern(command);
		for (int i = 0; name[i] != '\0'; i++) namesize++;
		name[namesize-1] = '\0';
		namesize--;
		newname = scannerp(command);
		for (int i = 0; newname[i] != '\0'; i++) sizenewfilename++;
		for (int i = 0; i<namesize; i++) {
			if (name[i] == '.') dot++;
			if (dot == 1) extsize++;
		}
		ext = new char[extsize]{};
		dot = 0;
		for (int i = 0; i<namesize; i++) {
			if (dot == 1) {
				ext[kext] = name[i];
				kext++;
			}
			if (name[i] == '.') dot++;
		}
		sizenew = sizenewfilename + extsize +1;
		newfilename = newname;
		newname = new char[sizenew] {};
		for (int i = 0; i < sizenew - 1; i++) {
			if (i < sizenewfilename) {
				newname[i] = newfilename[i];
			}
			else if (i == sizenewfilename) newname[i] = '.';
			else newname[i] = ext[i - sizenewfilename - 1];
		}
		name = readNameToReal(name, pathor);
		newname = readNameToReal(newname, pathor);
		int h;
		if ((h = rename(name, newname)) == 0) cout << "���� ������� ������������" << endl;
		else cout << "�� ������� ������������� ����" << endl;
	}
	//enter
	else if (flag[0] == 'e' && flag[1] == 'n' && flag[2] == 't') {
		name = scannern(command);
		if (name[0] == '^' && name[1] == '\0') {
			int sizepath = 0;
			char *up = new char[3]{ ".." };
			for (int i = 0; pathor[i] != '\0'; i++) sizepath++;
			sizepath++;
			char *testpathor = new char[sizepath] {};
			for (int i = 0; i < sizepath; i++) testpathor[i] = pathor[i];
			testpathor = enterFolder(testpathor, up);
			testpathor = pathToFind(testpathor);
			if(testfiles(FindFileData, hf, testpathor) !=0 )pathor = enterFolder(pathor, up);
			else cout << "�� ������� ������� �������" << endl;
		}
		else {
			int sizepath = 0;
			for (int i = 0; pathor[i] != '\0'; i++) sizepath++;
			sizepath++;
			char *testpathor = new char[sizepath] {};
			for (int i = 0; i < sizepath; i++) testpathor[i] = pathor[i];
			testpathor = enterFolder(testpathor, name);
			testpathor = pathToFind(testpathor);
			if (testfiles(FindFileData, hf, testpathor) != 0) pathor = enterFolder(pathor, name);
			else cout << "�� ������� ������� �������" << endl;
		}
		return pathor;
	}
	//change
	else if (flag[0] == 'c' && flag[1] == 'h' && flag[2] == 'n') {
		path = scannern(command);
		int sizepath = 0;
		for (int i = 0; path[i] != '\0'; i++) sizepath++;
		sizepath++;
		char *testpathor = new char[sizepath] {};
		for (int i = 0; i < sizepath; i++) testpathor[i] = path[i];
		testpathor = pathToFind(testpathor);
		if (testfiles(FindFileData, hf, testpathor) != 0 && path[sizepath-2] == '\\') pathor = path;
		else cout << "����������� ����� ����� ����" << endl;
	}
	system("pause");
	return pathor;
}
char* scannerf(char *command) {
	//��������� �������� �����
	const char del[] = { "delete" };
	const char copy[] = { "copy" };
	const char create[] = { "create" };
	const char rename[] = { "rename" };
	const char enter[] = { "enter" };
	const char help[] = { "help" };
	const char exit[] = { "exit" };
	const char change[] = { "change" };
	bool dl = false, cp = false, crt = false, rnm = false, en = false, hlp = false, ext = false, cn = false;
	int vrfdel = 0, vrfcp = 0, vrfcrt = 0, vrfrnm = 0, vrfen = 0, vrfhlp = 0, vrfext = 0, vrfcn = 0;
	for (int i = 0; i < 6; i++) {
		//if ��������� ��-�� ������� � ������ ������;
		//� �� ��� ������� ���������� ���������� ���� � "��������", 
		//�� ����� ������������ + ����� �� ���������� � ������� ��� ����� ������
		if (i <= 3) {
			if (command[i] == help[i]) vrfhlp++;
			if (command[i] == enter[i]) vrfen++;
			if (command[i] == exit[i]) vrfext++;
			if (command[i] == copy[i]) vrfcp++;
			if (command[i] == del[i]) vrfdel++;
			if (command[i] == create[i]) vrfcrt++;
			if (command[i] == rename[i]) vrfrnm++;
			if (command[i] == change[i]) vrfcn++;
		}
		else if (i == 4) {
			if (command[i] == enter[i]) vrfen++;
			if (command[i] == del[i]) vrfdel++;
			if (command[i] == create[i]) vrfcrt++;
			if (command[i] == rename[i]) vrfrnm++;
			if (command[i] == change[i]) vrfcn++;
		}
		else {
			if (command[i] == del[i]) vrfdel++;
			if (command[i] == create[i]) vrfcrt++;
			if (command[i] == rename[i]) vrfrnm++;
			if (command[i] == change[i]) vrfcn++;
		}
	}
	if (vrfdel == sizeof(del) - 1 && command[sizeof(del)-1] == '.') dl = true;
	else if (vrfcp == sizeof(copy) - 1 && command[sizeof(copy)-1] == '.') cp = true;
	else if (vrfcrt == sizeof(create) - 1 && command[sizeof(create)-1] == '.') crt = true;
	else if (vrfrnm == sizeof(rename) - 1 && command[sizeof(rename)-1] == '.') rnm = true;
	else if (vrfen == sizeof(enter) - 1 && command[sizeof(enter)-1] == '.') en = true;
	else if (vrfcn == sizeof(change) - 1 && command[sizeof(change) - 1] == '.') cn = true;
	else if (vrfhlp == sizeof(help) - 1) hlp = true;
	else if (vrfext == sizeof(exit) - 1) ext = true;
	char *a = new char[4]{};
	if (dl) strcpy(a, "dlt");
	else if (cp) strcpy(a, "cpy");
	else if (crt) strcpy(a, "crt");
	else if (rnm) strcpy(a, "rnm");
	else if (en) strcpy(a, "ent");
	else if (hlp) strcpy(a, "hlp");
	else if (ext) strcpy(a, "ext");
	else if (cn) strcpy(a, "chn");
	else {
		cout << "����������� ������� �������" << endl;
		system("pause");
		return nullptr;
	}
	return a;

}
void showmenu() {
	//����
	system("cls");
	cout << "\t��������� �������:" << endl;
	cout << "1. ���������� - copy.��������.����������.����" << endl;
	cout << "   (���� - ��� ����� � ���������� �����������, ����� ���� � � ����� ��������� \\)" << endl;
	cout << "2. ������� - create.��������.����������      (�������� ������� � ������� �����)" << endl;
	cout << "3. ������� - delete.��������.����������      (�������� ������ � ������� �����)" << endl;
	cout << "4. ������������� - rename.��������.����������.��������" << endl;
	cout << "5. ����� � ����� - enter.��������" << endl;
	cout << "6. ����� �� ������� ����� - enter.^ " << endl;
	cout << "7. �������� ���������� - help" << endl;
	cout << "8. ����� �� ��������� - exit" << endl;
	cout << "9. �������� ���� - change.���������������" << endl;
	system("pause");
	system("cls");
}
int showfiles(WIN32_FIND_DATA &FindFileData, HANDLE &hf, char *pathToFind) {
	//���������� �����
	hf = FindFirstFile(pathToFind, &FindFileData);
	if (hf == INVALID_HANDLE_VALUE) return 0;
	system("cls");
	cout << "--------------------------------------------------------------" << endl;
	do
	{
		cout << FindFileData.cFileName << endl;

	} while (FindNextFile(hf, &FindFileData));
	cout << "--------------------------------------------------------------" << endl;
	return 1;
}
int testfiles(WIN32_FIND_DATA &FindFileData, HANDLE &hf, char *pathToFind) {
	//������ ����, ���� �� ����������
	hf = FindFirstFile(pathToFind, &FindFileData);
	if (hf == INVALID_HANDLE_VALUE) return 0;
	return 1;
}
char* enterFolder(char *path1, char *foldername) {
	//���������� ��� ����������
	char *newpath;
	int pathsize = 0;
	for (int i = 0; path1[i] != '\0'; i++)pathsize++;
	int fldnamesize = 0;
	for (int i = 0; foldername[i] != '\0'; i++)fldnamesize++;
	newpath = new char[pathsize + fldnamesize + 1]{};
	strncpy(newpath, path1, pathsize);
	strncpy((newpath + pathsize), foldername, fldnamesize);
	newpath[pathsize + fldnamesize] = '\\';
	newpath[pathsize + fldnamesize + 1] = '\0';
	return newpath;
}
char* pathToFind(char *path1) {
	//�������������� ���� ��� showfiles � testfiles
	int size = 0;
	for (int i = 0; path1[i] != '\0'; i++)size++;
	char *a = new char[(size + 4)]{};
	for (int i = 0; i < size ; i++) {
		a[i] = path1[i];
	}
	a[size] = '*';
	a[size + 1] = '.';
	a[size + 2] = '*';
	return a;
}
//