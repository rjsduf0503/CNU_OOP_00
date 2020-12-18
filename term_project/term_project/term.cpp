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



//file의 내용을 한 줄 단위로 잘라서 vector로 저장하는 함수
void FileManager::toVector() { 
	ifstream file("test.txt"); //읽기 모드로 test.txt파일을 열어 file에 저장 
	if (file.is_open()) { //파일이 정상적으로 열린 경우
		string wordByWord = "", str = "";
		int wordSize = 0, totalSize = 0;
		//파일의 eof까지 돌며 한 단어씩 읽어 더해가며 한 줄씩 저장하되, 75바이트가 넘지 않도록 저장
		while (!file.eof()) {
			file >> wordByWord; //파일에서 한 단어씩 읽어 wordByWord에 저장
			wordSize = wordByWord.size();
			if (totalSize + wordSize > 75) {
				vec.push_back(str);
				str = wordByWord + " ";
				totalSize = wordSize + 1; //공백 포함이므로 + 1
			}
			else {
				str += wordByWord + " ";
				totalSize += wordSize + 1; //공백 포함이므로 + 1
			}

		}
		//마지막 줄은 75바이트 이하라 추가가 되지 않으므로 따로 추가
		vec.push_back(str); 
		limitLine = vec.size(); //현재 vec의 size로(줄 개수) limitLine 설정
		file.close(); //파일을 닫아줌
	}
	else { //파일 열기에 실패한 경우
		cout << "파일 열기 실패" << endl;
	}
}

//최대 line을 limitLine로 하여 현재 page를 출력하는 함수
void FileManager::getPage(int limitLine) {
	if (searchedLine != 0) { //검색한 경우라면
		thisLine = searchedLine; //현재 line을 검색한 line으로 설정
	}
	//최대 라인 번호 != 현재 라인 + 19한 라인(현재 페이지의 마지막 줄) && 최대 라인 번호 - 현재 라인 < 20
	//즉, 최대 라인이 90일 때 현재 라인이 71 이상이면 현재 라인은 71(90-19)
	else if (limitLine != (thisLine + 19)) { 
		if (limitLine - thisLine < 20) {
			thisLine = limitLine - 19;
		}
	}
	if (thisLine <= 0) { //현재 라인이 0보다 작거나 같은 경우는 1
		thisLine = 1;
	}

	//현재 라인이 최대 라인보다 작거나 같은 동안 한 줄씩 출력하며, 20줄 출력 후 break
	int flag = 0;
	while (thisLine <= limitLine) {
		cout.width(2);
		cout << thisLine << "| ";
		cout << vec[thisLine - 1] << endl;
		thisLine++; flag++;
		if (flag == 20) break;
	}

	if (searchedLine != 0) { //검색한 경우라면
		thisLine = searchedLine; //현재 라인을 검색한 라인으로 설정
		searchedLine = 0; //검색한 경우를 초기화
	}
	else { //검색한 경우가 아닐 때
		thisLine -= 20; //현재 라인을 20 감소시켜줌(다음 페이지 일땐 +20, 이전 페이지 일땐 -20만 하기위해)
	}
	whatInput("");
}

void FileManager::increasePointer() {
	thisLine += 20;
}
void FileManager::decreasePointer() {
	thisLine -= 20;
}

//명령어를 입력받는 함수, 올바른 명령어를 받을 때 까지 반복함
void FileManager::whatInput(string consoleMessage = "") {
	showMenu();
	cout << "  (콘솔메시지)";
	cout << consoleMessage;
	cout << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	cout << "  입력 : " && getline(cin, inputString) && cout << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	size_t find = inputString.find(' ');
	if (find != string::npos) {
		whatInput("명령어에 공백이 포함되었습니다. 다시 입력하세요.");
		return;
	}

	string inputWord = "";
	char inputChar = (char)inputString[0];
	switch (inputChar) {
	case 'n':
		if (inputString.size() == 1) {
			if (thisLine + 20 > limitLine) {
				whatInput("현재 페이지가 마지막 페이지 입니다. 다시 입력하세요.");
			}
			else {
				increasePointer();
				getPage(limitLine);
			}
		}
		else {
			whatInput("n 이외에 다른 문자를 입력하면 안됩니다. 다시 입력하세요.");
		}
		break;
	case 'p':
		if (inputString.size() == 1) {
			if (thisLine == 1) {
				whatInput("현재 페이지가 처음 페이지 입니다. 다시 입력하세요.");
			}
			else {
				decreasePointer();
				getPage(limitLine);
			}
		}
		else {
			whatInput("p 이외에 다른 문자를 입력하면 안됩니다. 다시 입력하세요.");
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
			whatInput("여는 괄호 혹은 닫는 괄호가 잘못되었습니다. 다시 입력하세요.");
			break;
		}
		else if (v.size() != 3) {
			whatInput("인자 개수가 다릅니다. 다시 입력하세요.");
			break;
		}

		//첫 번째 인자
		int temp = 0;
		char ch1[6] = { 0 };
		strcpy(ch1, v[0].c_str());
		for (int i = 2; i < sizeof(ch1); i++) {
			if (ch1[i] != '\0') { //null이 아닐 때
				if (65 <= ch1[i] && ch1[i] <= 90 || 97 <= ch1[i] && ch1[i] <= 122) {
					whatInput("숫자 부분에 문자 값을 입력하였습니다. 다시 입력하세요.");
					break;
				}
				else if (48 <= ch1[i] && ch1[i] <= 57) {
					temp = temp * 10 + (ch1[i] - '0');
				}
				else {
					whatInput("숫자 부분에 특수 문자 값을 입력하였습니다. 다시 입력하세요.");
					break;
				}
			}
		}
		i_parameter[0] = temp;
		temp = 0;

		if (i_parameter[0] < thisLine || i_parameter[0] > thisLine + 19 || i_parameter[0] > limitLine || i_parameter[0] <= 0) {
			whatInput("입력하신 라인은 현재 출력 창에 존재하지 않습니다. 다시 입력하세요.");
			break;
		}


		//두번째 인자
		char ch2[4] = { 0 };
		strcpy(ch2, v[1].c_str());
		for (int i = 0; i < sizeof(ch2); i++) {
			if (ch2[i] != '\0') {
				if (65 <= ch2[i] && ch2[i] <= 90 || 97 <= ch2[i] && ch2[i] <= 122) {
					whatInput("숫자 부분에 문자 값을 입력하였습니다. 다시 입력하세요.");
					break;
				}
				else if (48 <= ch2[i] && ch2[i] <= 57) {
					temp = temp * 10 + (ch2[i] - '0');
				}
				else {
					whatInput("숫자 부분에 특수 문자 값을 입력하였습니다. 다시 입력하세요.");
					break;
				}
			}
		}
		i_parameter[1] = temp;
		temp = 0;
		int wordsNum = getWordsNum(i_parameter[0]);
		if (i_parameter[1] > wordsNum) {
			whatInput("입력하신 라인에는 입력하신 번호의 단어가 존재하지 않습니다. 다시 입력하세요.");
			break;
		}

		//세 번째 인자
		int end = v[2].find(")");
		v[2].erase(end);
		inputWord = v[2];
		if (v[2].size() >= 75) {
			whatInput("75바이트 이상 출력 불가능합니다. 다시 입력하세요.");
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
			whatInput("여는 괄호 혹은 닫는 괄호가 잘못되었습니다. 다시 입력하세요.");
			break;
		}
		else if (v.size() != 2) {
			whatInput("인자 개수가 다릅니다. 다시 입력하세요.");
			break;
		}


		//첫 번째 인자
		int temp = 0;
		char ch1[6] = { 0 };
		strcpy(ch1, v[0].c_str());
		for (int i = 2; i < sizeof(ch1); i++) {
			if (ch1[i] != '\0') {
				if (65 <= ch1[i] && ch1[i] <= 90 || 97 <= ch1[i] && ch1[i] <= 122) {
					whatInput("숫자 부분에 문자 값을 입력하였습니다. 다시 입력하세요.");
					break;
				}
				else if (48 <= ch1[i] && ch1[i] <= 57) {
					temp = temp * 10 + (ch1[i] - '0');
				}
				else {
					whatInput("숫자 부분에 특수 문자 값을 입력하였습니다. 다시 입력하세요.");
					break;
				}
			}
		}
		j_parameter[0] = temp;
		temp = 0;
		if (j_parameter[0] < thisLine || j_parameter[0] > thisLine + 19 || j_parameter[0] > limitLine || j_parameter[0] <= 0) {
			whatInput("입력하신 라인은 현재 출력 창에 존재하지 않습니다. 다시 입력하세요.");
			break;
		}

		//두 번째 인자
		int end = v[1].find(")");
		v[1].erase(end);
		char ch2[4] = { 0 };
		strcpy(ch2, v[1].c_str());


		for (int i = 0; i < sizeof(ch2); i++) {
			if (ch2[i] != '\0') {
				if (65 <= ch2[i] && ch2[i] <= 90 || 97 <= ch2[i] && ch2[i] <= 122) {
					whatInput("숫자 부분에 문자 값을 입력하였습니다. 다시 입력하세요.");
					break;
				}
				else if (48 <= ch2[i] && ch2[i] <= 57) {
					temp = temp * 10 + (ch2[i] - '0');
				}
				else {
					whatInput("숫자 부분에 특수 문자 값을 입력하였습니다. 다시 입력하세요.");
					break;
				}
			}
		}
		j_parameter[1] = temp;
		temp = 0;
		int wordsNum = getWordsNum(j_parameter[0]);
		if (j_parameter[1] > wordsNum) {
			whatInput("입력하신 라인에는 입력하신 번호의 단어가 존재하지 않습니다. 다시 입력하세요.");
			break;
		}


		deleteText(j_parameter[0], j_parameter[1]);
		getPage(limitLine);
		break;
	}
	case 's':
	{
		if (inputString[1] != '(' || inputString[inputString.size() - 1] != ')') {
			whatInput("여는 괄호 혹은 닫는 괄호가 잘못되었습니다. 다시 입력하세요.");
			break;
		}
		for (int i = 2; i < inputString.size() - 1; i++) {
			if (inputString[i] == ',') {
				whatInput("인자의 개수가 다릅니다. 다시 입력하세요.");
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
			whatInput("여는 괄호 혹은 닫는 괄호가 잘못되었습니다. 다시 입력하세요.");
			break;
		}
		else if (v.size() != 2) {
			whatInput("인자 개수가 다릅니다. 다시 입력하세요.");
			break;
		}

		//첫 번째 인자
		int temp = 0;
		char ch1[75] = { 0 };
		strcpy(ch1, v[0].c_str());
		for (int i = 2; i < sizeof(ch1); i++) {
			if (ch1[i] != '\0') {
				s_parameter[0] += ch1[i];
			}
		}
		//두 번째 인자
		int end = v[1].find(")");
		v[1].erase(end);
		s_parameter[1] = v[1];
		if (v[1].size() >= 75 || v[0].size() >= 77) {
			whatInput("75바이트 이상 출력 불가능합니다. 다시 입력하세요.");
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
			whatInput("t 이외에 다른 문자를 입력하면 안됩니다. 다시 입력하세요.");
		}
		break;
	default:
		whatInput("다시 입력하세요.");
		break;
	}
}

//lineNum 줄의 wordNum 단어 뒤에 inputWord를 삽입하는 함수
void FileManager::insertText(int lineNum, int wordNum, string inputWord) {
	token.clear(); //token 사용 전 초기화
	stringstream ss(vec[lineNum - 1]); //찾고자 하는 줄을 가져와 ss에 저장
	string buf = "";
	while (ss >> buf) { //ss에서 한 단어씩(띄어쓰기 기준) 잘라서 buf에 저장하고
		token.push_back(buf); //buf를 token vector에 저장
	}

	token.insert(token.begin() + wordNum, inputWord); //token의 wordNum 뒤에 inputWord를 삽입
	string str = "";
	//str에 token의 값들을 띄어쓰기와 함께 저장
	for (int i = 0; i < token.size(); i++) {
		str += token[i] + " ";
	}
	token.clear(); //token 초기화

	vec.erase(vec.begin() + lineNum - 1); //inputWord가 추가되기 전의 vec에서의 줄을 지우고
	vec.insert(vec.begin() + lineNum - 1, str); //추가된 줄을 삽입해줌
	modifyVector(); //혹시 그 줄이 75바이트가 넘어갈 수도 있으니 modifyVector()함수를 불러와 vec를 수정

}

//vector의 값이 바뀌었을 때 출력값도 바꾸기 위한 함수
void FileManager::modifyVector() { 
	string s; //기존 vector의 내용을 저장하기 위한 변수

	//s에 vec의 내용 다 저장
	for (int i = 0; i < vec.size(); i++) {
		s += vec[i];
	}
	vec.clear(); //vec의 내용 지우기

	int bufSize = 0, tempSize = 0;
	string buf = "", str = ""; //str은 vec에 추가할 한 줄
	istringstream iss(s);
	while (getline(iss, buf, ' ')) { //iss에서 띄어쓰기를 기준으로 받아와 buf에 저장
		bufSize = buf.size(); //buf의 size
		if (bufSize + tempSize <= 75) { //현재 buf의 크기와 tempSize의 합이 75byte 이하라면
			str += buf + " "; //str에 buf + " " 를 합쳐주고
			tempSize += bufSize + 1; //tempSize도 bufSize +1 만큼 늘려줌
		}
		else { //75바이트를 초과하면
			vec.push_back(str); //buf의 값을 넣기 전의 str(75바이트 초과하지 않음)을 vec에 추가
			str = buf + " "; //str은 현재 buf + " "로 초기화
			tempSize = bufSize + 1; //tempSize도 bufSize + 1로 초기화
		}
	}
	//최종적으로 vec에 마지막 str을 추가해주고 vec의 크기(줄 개수)로 마지막 줄의 번호를 입력해줌
	vec.push_back(str);
	limitLine = vec.size();
}

//lineNum 줄의 wordNum 번째 단어를 삭제하는 함수
void FileManager::deleteText(int lineNum, int wordNum) {
	token.clear(); //token 사용 전 초기화
	stringstream ss(vec[lineNum - 1]); //찾고자 하는 줄을 가져와 ss에 저장
	string buf = "";
	while (ss >> buf) { //ss에서 한 단어씩(띄어쓰기 기준) 잘라서 buf에 저장하고
		token.push_back(buf); //buf를 token vector에 저장
	}

	token.erase(token.begin() + wordNum - 1); //token의 wordNum번째 단어를 삭제
	string str = "";
	//str에 token의 값들을 띄어쓰기와 함께 저장
	for (int i = 0; i < token.size(); i++) {
		str += token[i] + " ";
	}
	token.clear(); //token 초기화

	vec.erase(vec.begin() + lineNum - 1); //wordNum번째 단어를 삭제하기 전의 vec에서의 줄을 지우고
	vec.insert(vec.begin() + lineNum - 1, str); //삭제된 줄을 삽입해줌
	modifyVector(); //혹시 모를 변경사항을 위해 modifyVector를 불러옴

}

//모든 inputWord를 replaceWord로 변경
void FileManager::changeText(string inputWord, string replaceWord) {
	bool isExist = false; //inputWord가 존재하는지의 여부
	token.clear();//token 사용 전 초기화
	string s = "";
	for (int i = 0; i < vec.size(); i++) { //vec의 모든 값을 s에 저장
		s += vec[i];
	}
	vec.clear(); //후 vec 초기화
	stringstream ss(s);
	string buf = "";
	while (ss >> buf) { //ss를 띄어쓰기 기준으로 잘라서 token vector에 저장
		token.push_back(buf);
	}
	string changedString = ""; //inputWord를 replaceWord로 변환 후의 string
	//모든 token을 돌며
	for (int i = 0; i < token.size(); i++) {
		if (inputWord == token[i]) {  //inputWord와 일치하는 token이 있을 때
			isExist = true; //존재한다고 변경
			token.erase(token.begin() + i); //inputWord가 있는 token을 지우고
			token.insert(token.begin() + i, replaceWord); //replaceWord로 대체하여 insert
		}
		changedString += token[i] + " "; //그 token과 공백을 changedString에 추가
	}
	token.clear(); //token 초기화
	if (isExist == false) { //inputWord와 일치하는 단어가 없을 경우
		whatInput("입력하신 단어는 파일에 존재하지 않습니다. 다시 입력하세요.");
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

//첫 번째 inputWord를 찾아 그 줄이 출력 창의 첫 라인에 위치하도록 조정하는 함수
void FileManager::searchText(string inputWord) {
	token.clear(); //token 사용 전 초기화
	string s = "";
	//vec을 돌며
	for (int i = 0; i < vec.size(); i++) {
		s = vec[i]; //s에 저장
		stringstream ss(s);
		string buf = "";
		while (ss >> buf) { //띄어쓰기를 기준으로 buf에 저장하며
			token.push_back(buf); //그 buf값을 token vector에 저장
		}
		for (int j = 0; j < token.size(); j++) {
			if (inputWord == token[j]) { //token을 돌며 inputWord와 일치하는 값이 있다면
				searchedLine = i + 1; //그 라인을 searchedLine으로 설정
				return; //후 함수 종료
			}
		}
	}

	//종료되지 않았다면 단어가 존재하지 않는 것
	whatInput("입력하신 단어는 파일에 존재하지 않습니다. 다시 입력하세요.");
}

//현재까지 작업한 파일을 저장하고 종료하는 함수
void FileManager::saveAndQuit() {
	ofstream modifiedFile;
	modifiedFile.open("test.txt");
	if (modifiedFile.is_open()) {
		for (int i = 0; i < vec.size(); i++) {
			modifiedFile.write(vec[i].c_str(), vec[i].size());
		}
	}
	else {
		whatInput("파일 열기 실패");
		return;
	}
	modifiedFile.close();
}

//입력받은 string이 숫자인지 체크하는 함수
bool FileManager::isNumber(const string& str) { 
	for (char const& c : str) { //한 글자씩 isdigit 함수로 보며 숫자가 아니면 false
		if (std::isdigit(c) == 0) return false;
	}
	return true;
}

//입력 받은 줄의 단어 개수를 반환하는 함수
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
	cout << "  n:다음페이지, p:이전 페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료" << endl;
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


	//싱글톤 패턴이 잘 적용되었는지 보기 위함
	/*cout << "main : " << manager->get_log_data() << endl;
	Logger_User_A();
	Logger_User_B();*/
}