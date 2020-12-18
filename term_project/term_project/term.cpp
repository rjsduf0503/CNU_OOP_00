using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#define lineWidth 75
#define lineHeight 20

class FileManager {
public:
	static FileManager* getInstance() {
		if (instance == nullptr) {
			instance = new FileManager();
			atexit(deleteInstance);
		}
		return instance;
	}
	static void deleteInstance() {
		if (instance) {
			delete instance;
			instance = nullptr;
		}
	}
	void toVector();
	void getPage(int limitLine);
	void decreasePointer();
	void increasePointer();
	void whatInput(string consoleMessage);
	void showMenu();
	void insertText(int lineNum, int wordNum, string insertWord);
	void deleteText(int lineNum, int wordNum);
	void searchText(string inputWord);
	void changeText(string inputWord, string replaceWord);
	int getWordsNum(int searchLine);
	bool isNumber(const string& str);
	void saveAndQuit();
	void modifyVector();

	int getThisLine() {
		return this->thisLine;
	}
	void setThisLine(int line) {
		this->thisLine = line;
	}
	int getLimitLine() {
		return this->limitLine;
	}
	void setLimitLine(int line) {
		this->limitLine = line;
	}
	int getSearchedLine() {
		return this->searchedLine;
	}
	void setSearchedLine(int line) {
		this->searchedLine = line;
	}
	string getInputString() {
		return this->inputString;
	}
	void setInputString(string str) {
		this->inputString = str;
	}

	/*int get_log_data() {
		return log_value;
	}
	void set_log_data(int v) {
		log_value = v;
	}*/

private:
	vector<string> vec;
	vector<string> token;

	/*int log_value;*/

	int thisLine = 1;
	int limitLine = 0;
	int searchedLine = 0;
	string inputString;

	FileManager() {};
	~FileManager() {};

	static FileManager* instance;
};

FileManager* FileManager::instance = nullptr;



//file�� ������ �� �� ������ �߶� vector�� �����ϴ� �Լ�
void FileManager::toVector() { 
	ifstream file("test.txt"); //�б� ���� test.txt������ ���� file�� ���� 
	if (file.is_open()) { //������ ���������� ���� ���
		string wordByWord = "", str = "";
		int wordSize = 0, totalSize = 0;
		//������ eof���� ���� �� �ܾ �о� ���ذ��� �� �پ� �����ϵ�, 75����Ʈ�� ���� �ʵ��� ����
		while (!file.eof()) {
			file >> wordByWord; //���Ͽ��� �� �ܾ �о� wordByWord�� ����
			wordSize = wordByWord.size();
			if (totalSize + wordSize > 75) {
				vec.push_back(str);
				str = wordByWord + " ";
				totalSize = wordSize + 1; //���� �����̹Ƿ� + 1
			}
			else {
				str += wordByWord + " ";
				totalSize += wordSize + 1; //���� �����̹Ƿ� + 1
			}

		}
		//������ ���� 75����Ʈ ���϶� �߰��� ���� �����Ƿ� ���� �߰�
		vec.push_back(str); 
		limitLine = vec.size(); //���� vec�� size��(�� ����) limitLine ����
		file.close(); //������ �ݾ���
	}
	else { //���� ���⿡ ������ ���
		cout << "���� ���� ����" << endl;
	}
}

//�ִ� line�� limitLine�� �Ͽ� ���� page�� ����ϴ� �Լ�
void FileManager::getPage(int limitLine) {
	if (searchedLine != 0) { //�˻��� �����
		thisLine = searchedLine; //���� line�� �˻��� line���� ����
	}
	//�ִ� ���� ��ȣ != ���� ���� + 19�� ����(���� �������� ������ ��) && �ִ� ���� ��ȣ - ���� ���� < 20
	//��, �ִ� ������ 90�� �� ���� ������ 71 �̻��̸� ���� ������ 71(90-19)
	else if (limitLine != (thisLine + 19)) { 
		if (limitLine - thisLine < 20) {
			thisLine = limitLine - 19;
		}
	}
	if (thisLine <= 0) { //���� ������ 0���� �۰ų� ���� ���� 1
		thisLine = 1;
	}

	//���� ������ �ִ� ���κ��� �۰ų� ���� ���� �� �پ� ����ϸ�, 20�� ��� �� break
	int flag = 0;
	while (thisLine <= limitLine) {
		cout.width(2);
		cout << thisLine << "| ";
		cout << vec[thisLine - 1] << endl;
		thisLine++; flag++;
		if (flag == 20) break;
	}

	if (searchedLine != 0) { //�˻��� �����
		thisLine = searchedLine; //���� ������ �˻��� �������� ����
		searchedLine = 0; //�˻��� ��츦 �ʱ�ȭ
	}
	else { //�˻��� ��찡 �ƴ� ��
		thisLine -= 20; //���� ������ 20 ���ҽ�����(���� ������ �϶� +20, ���� ������ �϶� -20�� �ϱ�����)
	}
	whatInput("");
}

void FileManager::increasePointer() {
	thisLine += 20;
}
void FileManager::decreasePointer() {
	thisLine -= 20;
}

//��ɾ �Է¹޴� �Լ�, �ùٸ� ��ɾ ���� �� ���� �ݺ���
void FileManager::whatInput(string consoleMessage = "") {
	showMenu();
	cout << "  (�ָܼ޽���)";
	cout << consoleMessage;
	cout << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	cout << "  �Է� : " && getline(cin, inputString) && cout << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	size_t find = inputString.find(' ');
	if (find != string::npos) {
		whatInput("��ɾ ������ ���ԵǾ����ϴ�. �ٽ� �Է��ϼ���.");
		return;
	}

	string inputWord = "";
	char inputChar = (char)inputString[0];
	switch (inputChar) {
	case 'n':
		if (inputString.size() == 1) {
			if (thisLine + 20 > limitLine) {
				whatInput("���� �������� ������ ������ �Դϴ�. �ٽ� �Է��ϼ���.");
			}
			else {
				increasePointer();
				getPage(limitLine);
			}
		}
		else {
			whatInput("n �̿ܿ� �ٸ� ���ڸ� �Է��ϸ� �ȵ˴ϴ�. �ٽ� �Է��ϼ���.");
		}
		break;
	case 'p':
		if (inputString.size() == 1) {
			if (thisLine == 1) {
				whatInput("���� �������� ó�� ������ �Դϴ�. �ٽ� �Է��ϼ���.");
			}
			else {
				decreasePointer();
				getPage(limitLine);
			}
		}
		else {
			whatInput("p �̿ܿ� �ٸ� ���ڸ� �Է��ϸ� �ȵ˴ϴ�. �ٽ� �Է��ϼ���.");
		}
		break;
	case 'i':
	{
		int i_parameter[2];
		stringstream ss(inputString);
		string buf = "";
		vector<string> v;
		v.clear();
		while (getline(ss, buf, ',')) {
			v.push_back(buf);
		}
		if (inputString[1] != '(' || inputString[inputString.length() - 1] != ')') {
			whatInput("���� ��ȣ Ȥ�� �ݴ� ��ȣ�� �߸��Ǿ����ϴ�. �ٽ� �Է��ϼ���.");
			break;
		}
		else if (v.size() != 3) {
			whatInput("���� ������ �ٸ��ϴ�. �ٽ� �Է��ϼ���.");
			break;
		}

		//ù ��° ����
		int temp = 0;
		char ch1[6] = { 0 };
		strcpy(ch1, v[0].c_str());
		for (int i = 2; i < sizeof(ch1); i++) {
			if (ch1[i] != '\0') { //null�� �ƴ� ��
				if (65 <= ch1[i] && ch1[i] <= 90 || 97 <= ch1[i] && ch1[i] <= 122) {
					whatInput("���� �κп� ���� ���� �Է��Ͽ����ϴ�. �ٽ� �Է��ϼ���.");
					break;
				}
				else if (48 <= ch1[i] && ch1[i] <= 57) {
					temp = temp * 10 + (ch1[i] - '0');
				}
				else {
					whatInput("���� �κп� Ư�� ���� ���� �Է��Ͽ����ϴ�. �ٽ� �Է��ϼ���.");
					break;
				}
			}
		}
		i_parameter[0] = temp;
		temp = 0;

		if (i_parameter[0] < thisLine || i_parameter[0] > thisLine + 19 || i_parameter[0] > limitLine || i_parameter[0] <= 0) {
			whatInput("�Է��Ͻ� ������ ���� ��� â�� �������� �ʽ��ϴ�. �ٽ� �Է��ϼ���.");
			break;
		}


		//�ι�° ����
		char ch2[4] = { 0 };
		strcpy(ch2, v[1].c_str());
		for (int i = 0; i < sizeof(ch2); i++) {
			if (ch2[i] != '\0') {
				if (65 <= ch2[i] && ch2[i] <= 90 || 97 <= ch2[i] && ch2[i] <= 122) {
					whatInput("���� �κп� ���� ���� �Է��Ͽ����ϴ�. �ٽ� �Է��ϼ���.");
					break;
				}
				else if (48 <= ch2[i] && ch2[i] <= 57) {
					temp = temp * 10 + (ch2[i] - '0');
				}
				else {
					whatInput("���� �κп� Ư�� ���� ���� �Է��Ͽ����ϴ�. �ٽ� �Է��ϼ���.");
					break;
				}
			}
		}
		i_parameter[1] = temp;
		temp = 0;
		int wordsNum = getWordsNum(i_parameter[0]);
		if (i_parameter[1] > wordsNum) {
			whatInput("�Է��Ͻ� ���ο��� �Է��Ͻ� ��ȣ�� �ܾ �������� �ʽ��ϴ�. �ٽ� �Է��ϼ���.");
			break;
		}

		//�� ��° ����
		int end = v[2].find(")");
		v[2].erase(end);
		inputWord = v[2];
		if (v[2].size() >= 75) {
			whatInput("75����Ʈ �̻� ��� �Ұ����մϴ�. �ٽ� �Է��ϼ���.");
			break;
		}

		insertText(i_parameter[0], i_parameter[1], inputWord);
		getPage(limitLine);
		break;
	}


	case 'd':
	{
		int j_parameter[2];
		stringstream ss(inputString);
		string buf = "";
		vector<string> v;
		v.clear();
		while (getline(ss, buf, ',')) {
			v.push_back(buf);
		}
		if (inputString[1] != '(' || inputString[inputString.size() - 1] != ')') {
			whatInput("���� ��ȣ Ȥ�� �ݴ� ��ȣ�� �߸��Ǿ����ϴ�. �ٽ� �Է��ϼ���.");
			break;
		}
		else if (v.size() != 2) {
			whatInput("���� ������ �ٸ��ϴ�. �ٽ� �Է��ϼ���.");
			break;
		}


		//ù ��° ����
		int temp = 0;
		char ch1[6] = { 0 };
		strcpy(ch1, v[0].c_str());
		for (int i = 2; i < sizeof(ch1); i++) {
			if (ch1[i] != '\0') {
				if (65 <= ch1[i] && ch1[i] <= 90 || 97 <= ch1[i] && ch1[i] <= 122) {
					whatInput("���� �κп� ���� ���� �Է��Ͽ����ϴ�. �ٽ� �Է��ϼ���.");
					break;
				}
				else if (48 <= ch1[i] && ch1[i] <= 57) {
					temp = temp * 10 + (ch1[i] - '0');
				}
				else {
					whatInput("���� �κп� Ư�� ���� ���� �Է��Ͽ����ϴ�. �ٽ� �Է��ϼ���.");
					break;
				}
			}
		}
		j_parameter[0] = temp;
		temp = 0;
		if (j_parameter[0] < thisLine || j_parameter[0] > thisLine + 19 || j_parameter[0] > limitLine || j_parameter[0] <= 0) {
			whatInput("�Է��Ͻ� ������ ���� ��� â�� �������� �ʽ��ϴ�. �ٽ� �Է��ϼ���.");
			break;
		}

		//�� ��° ����
		int end = v[1].find(")");
		v[1].erase(end);
		char ch2[4] = { 0 };
		strcpy(ch2, v[1].c_str());


		for (int i = 0; i < sizeof(ch2); i++) {
			if (ch2[i] != '\0') {
				if (65 <= ch2[i] && ch2[i] <= 90 || 97 <= ch2[i] && ch2[i] <= 122) {
					whatInput("���� �κп� ���� ���� �Է��Ͽ����ϴ�. �ٽ� �Է��ϼ���.");
					break;
				}
				else if (48 <= ch2[i] && ch2[i] <= 57) {
					temp = temp * 10 + (ch2[i] - '0');
				}
				else {
					whatInput("���� �κп� Ư�� ���� ���� �Է��Ͽ����ϴ�. �ٽ� �Է��ϼ���.");
					break;
				}
			}
		}
		j_parameter[1] = temp;
		temp = 0;
		int wordsNum = getWordsNum(j_parameter[0]);
		if (j_parameter[1] > wordsNum) {
			whatInput("�Է��Ͻ� ���ο��� �Է��Ͻ� ��ȣ�� �ܾ �������� �ʽ��ϴ�. �ٽ� �Է��ϼ���.");
			break;
		}


		deleteText(j_parameter[0], j_parameter[1]);
		getPage(limitLine);
		break;
	}
	case 's':
	{
		if (inputString[1] != '(' || inputString[inputString.size() - 1] != ')') {
			whatInput("���� ��ȣ Ȥ�� �ݴ� ��ȣ�� �߸��Ǿ����ϴ�. �ٽ� �Է��ϼ���.");
			break;
		}
		for (int i = 2; i < inputString.size() - 1; i++) {
			if (inputString[i] == ',') {
				whatInput("������ ������ �ٸ��ϴ�. �ٽ� �Է��ϼ���.");
				break;
			}
			inputWord += inputString[i];
		}
		searchText(inputWord);
		getPage(limitLine);
		break;
	}
	case 'c':
	{
		string s_parameter[2];
		stringstream ss(inputString);
		string buf = "";
		vector<string> v;
		v.clear();
		while (getline(ss, buf, ',')) {
			v.push_back(buf);
		}
		if (inputString[1] != '(' || inputString[inputString.size() - 1] != ')') {
			whatInput("���� ��ȣ Ȥ�� �ݴ� ��ȣ�� �߸��Ǿ����ϴ�. �ٽ� �Է��ϼ���.");
			break;
		}
		else if (v.size() != 2) {
			whatInput("���� ������ �ٸ��ϴ�. �ٽ� �Է��ϼ���.");
			break;
		}

		//ù ��° ����
		int temp = 0;
		char ch1[75] = { 0 };
		strcpy(ch1, v[0].c_str());
		for (int i = 2; i < sizeof(ch1); i++) {
			if (ch1[i] != '\0') {
				s_parameter[0] += ch1[i];
			}
		}
		//�� ��° ����
		int end = v[1].find(")");
		v[1].erase(end);
		s_parameter[1] = v[1];
		if (v[1].size() >= 75 || v[0].size() >= 77) {
			whatInput("75����Ʈ �̻� ��� �Ұ����մϴ�. �ٽ� �Է��ϼ���.");
			break;
		}
		changeText(s_parameter[0], s_parameter[1]);
		getPage(limitLine);
		break;
	}
	case 't':
		if (inputString.size() == 1) {
			saveAndQuit();
		}
		else {
			whatInput("t �̿ܿ� �ٸ� ���ڸ� �Է��ϸ� �ȵ˴ϴ�. �ٽ� �Է��ϼ���.");
		}
		break;
	default:
		whatInput("�ٽ� �Է��ϼ���.");
		break;
	}
}

//lineNum ���� wordNum �ܾ� �ڿ� inputWord�� �����ϴ� �Լ�
void FileManager::insertText(int lineNum, int wordNum, string inputWord) {
	token.clear(); //token ��� �� �ʱ�ȭ
	stringstream ss(vec[lineNum - 1]); //ã���� �ϴ� ���� ������ ss�� ����
	string buf = "";
	while (ss >> buf) { //ss���� �� �ܾ(���� ����) �߶� buf�� �����ϰ�
		token.push_back(buf); //buf�� token vector�� ����
	}

	token.insert(token.begin() + wordNum, inputWord); //token�� wordNum �ڿ� inputWord�� ����
	string str = "";
	//str�� token�� ������ ����� �Բ� ����
	for (int i = 0; i < token.size(); i++) {
		str += token[i] + " ";
	}
	token.clear(); //token �ʱ�ȭ

	vec.erase(vec.begin() + lineNum - 1); //inputWord�� �߰��Ǳ� ���� vec������ ���� �����
	vec.insert(vec.begin() + lineNum - 1, str); //�߰��� ���� ��������
	modifyVector(); //Ȥ�� �� ���� 75����Ʈ�� �Ѿ ���� ������ modifyVector()�Լ��� �ҷ��� vec�� ����

}

//vector�� ���� �ٲ���� �� ��°��� �ٲٱ� ���� �Լ�
void FileManager::modifyVector() { 
	string s; //���� vector�� ������ �����ϱ� ���� ����

	//s�� vec�� ���� �� ����
	for (int i = 0; i < vec.size(); i++) {
		s += vec[i];
	}
	vec.clear(); //vec�� ���� �����

	int bufSize = 0, tempSize = 0;
	string buf = "", str = ""; //str�� vec�� �߰��� �� ��
	istringstream iss(s);
	while (getline(iss, buf, ' ')) { //iss���� ���⸦ �������� �޾ƿ� buf�� ����
		bufSize = buf.size(); //buf�� size
		if (bufSize + tempSize <= 75) { //���� buf�� ũ��� tempSize�� ���� 75byte ���϶��
			str += buf + " "; //str�� buf + " " �� �����ְ�
			tempSize += bufSize + 1; //tempSize�� bufSize +1 ��ŭ �÷���
		}
		else { //75����Ʈ�� �ʰ��ϸ�
			vec.push_back(str); //buf�� ���� �ֱ� ���� str(75����Ʈ �ʰ����� ����)�� vec�� �߰�
			str = buf + " "; //str�� ���� buf + " "�� �ʱ�ȭ
			tempSize = bufSize + 1; //tempSize�� bufSize + 1�� �ʱ�ȭ
		}
	}
	//���������� vec�� ������ str�� �߰����ְ� vec�� ũ��(�� ����)�� ������ ���� ��ȣ�� �Է�����
	vec.push_back(str);
	limitLine = vec.size();
}

//lineNum ���� wordNum ��° �ܾ �����ϴ� �Լ�
void FileManager::deleteText(int lineNum, int wordNum) {
	token.clear(); //token ��� �� �ʱ�ȭ
	stringstream ss(vec[lineNum - 1]); //ã���� �ϴ� ���� ������ ss�� ����
	string buf = "";
	while (ss >> buf) { //ss���� �� �ܾ(���� ����) �߶� buf�� �����ϰ�
		token.push_back(buf); //buf�� token vector�� ����
	}

	token.erase(token.begin() + wordNum - 1); //token�� wordNum��° �ܾ ����
	string str = "";
	//str�� token�� ������ ����� �Բ� ����
	for (int i = 0; i < token.size(); i++) {
		str += token[i] + " ";
	}
	token.clear(); //token �ʱ�ȭ

	vec.erase(vec.begin() + lineNum - 1); //wordNum��° �ܾ �����ϱ� ���� vec������ ���� �����
	vec.insert(vec.begin() + lineNum - 1, str); //������ ���� ��������
	modifyVector(); //Ȥ�� �� ��������� ���� modifyVector�� �ҷ���

}

//��� inputWord�� replaceWord�� ����
void FileManager::changeText(string inputWord, string replaceWord) {
	bool isExist = false; //inputWord�� �����ϴ����� ����
	token.clear();//token ��� �� �ʱ�ȭ
	string s = "";
	for (int i = 0; i < vec.size(); i++) { //vec�� ��� ���� s�� ����
		s += vec[i];
	}
	vec.clear(); //�� vec �ʱ�ȭ
	stringstream ss(s);
	string buf = "";
	while (ss >> buf) { //ss�� ���� �������� �߶� token vector�� ����
		token.push_back(buf);
	}
	string changedString = ""; //inputWord�� replaceWord�� ��ȯ ���� string
	//��� token�� ����
	for (int i = 0; i < token.size(); i++) {
		if (inputWord == token[i]) {  //inputWord�� ��ġ�ϴ� token�� ���� ��
			isExist = true; //�����Ѵٰ� ����
			token.erase(token.begin() + i); //inputWord�� �ִ� token�� �����
			token.insert(token.begin() + i, replaceWord); //replaceWord�� ��ü�Ͽ� insert
		}
		changedString += token[i] + " "; //�� token�� ������ changedString�� �߰�
	}
	token.clear(); //token �ʱ�ȭ
	if (isExist == false) { //inputWord�� ��ġ�ϴ� �ܾ ���� ���
		whatInput("�Է��Ͻ� �ܾ�� ���Ͽ� �������� �ʽ��ϴ�. �ٽ� �Է��ϼ���.");
		return;
	}
	int bufSize = 0, tempSize = 0;
	istringstream iss(changedString);
	buf = "";
	string str;
	while (getline(iss, buf, ' ')) {
		bufSize = buf.size();
		if (bufSize + tempSize <= 75) {
			str += buf + " ";
			tempSize += bufSize + 1;
		}
		else {
			vec.push_back(str);
			str = buf + " ";
			tempSize = bufSize + 1;
		}
	}
	vec.push_back(str);
	limitLine = vec.size();
}

//ù ��° inputWord�� ã�� �� ���� ��� â�� ù ���ο� ��ġ�ϵ��� �����ϴ� �Լ�
void FileManager::searchText(string inputWord) {
	token.clear(); //token ��� �� �ʱ�ȭ
	string s = "";
	//vec�� ����
	for (int i = 0; i < vec.size(); i++) {
		s = vec[i]; //s�� ����
		stringstream ss(s);
		string buf = "";
		while (ss >> buf) { //���⸦ �������� buf�� �����ϸ�
			token.push_back(buf); //�� buf���� token vector�� ����
		}
		for (int j = 0; j < token.size(); j++) {
			if (inputWord == token[j]) { //token�� ���� inputWord�� ��ġ�ϴ� ���� �ִٸ�
				searchedLine = i + 1; //�� ������ searchedLine���� ����
				return; //�� �Լ� ����
			}
		}
	}

	//������� �ʾҴٸ� �ܾ �������� �ʴ� ��
	whatInput("�Է��Ͻ� �ܾ�� ���Ͽ� �������� �ʽ��ϴ�. �ٽ� �Է��ϼ���.");
}

//������� �۾��� ������ �����ϰ� �����ϴ� �Լ�
void FileManager::saveAndQuit() {
	ofstream modifiedFile;
	modifiedFile.open("test.txt");
	if (modifiedFile.is_open()) {
		for (int i = 0; i < vec.size(); i++) {
			modifiedFile.write(vec[i].c_str(), vec[i].size());
		}
	}
	else {
		whatInput("���� ���� ����");
		return;
	}
	modifiedFile.close();
}

//�Է¹��� string�� �������� üũ�ϴ� �Լ�
bool FileManager::isNumber(const string& str) { 
	for (char const& c : str) { //�� ���ھ� isdigit �Լ��� ���� ���ڰ� �ƴϸ� false
		if (std::isdigit(c) == 0) return false;
	}
	return true;
}

//�Է� ���� ���� �ܾ� ������ ��ȯ�ϴ� �Լ�
int FileManager::getWordsNum(int searchLine) {
	stringstream ss(vec[searchLine - 1]);
	string buf = "";
	token.clear();
	while (ss >> buf) {
		token.push_back(buf);
	}
	return token.size();
}

void FileManager::showMenu() {
	cout << "-----------------------------------------------------------------------------------------" << endl;
	cout << "  n:����������, p:���� ������, i:����, d:����, c:����, s:ã��, t:����������" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
}





//void Logger_User_A(void) {
//	FileManager::getInstance()->set_log_data(1);
//	cout << "A : " << FileManager::getInstance()->get_log_data() << endl;
//}
//void Logger_User_B(void) {
//	FileManager::getInstance()->set_log_data(2);
//	cout << "B : " << FileManager::getInstance()->get_log_data() << endl;
//}



int main(void) {
	FileManager* manager = FileManager::getInstance();
	manager->toVector();
	manager->getPage(manager->getLimitLine());


	//�̱��� ������ �� ����Ǿ����� ���� ����
	/*cout << "main : " << manager->get_log_data() << endl;
	Logger_User_A();
	Logger_User_B();*/
}