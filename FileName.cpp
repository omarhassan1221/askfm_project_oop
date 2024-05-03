#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <fstream>
#include <string>
using namespace std;
class User;
class Question;
class Answer;
class base;
class System;
vector<User>user_save;
class base {
protected:
	int ID;
	int From_ID;
	int To_ID;
};
class Question : public base {

public:
	friend class User;
	string quesion;
	friend class base;
	friend class System;
	Question() {};
	Question(string que, int id, int from_id, int to_id) {
		this->quesion = que;
		this->ID = id;
		this->From_ID = from_id;
		this->To_ID = to_id;
	}
};
vector<Question>questions_save;
class Answer :base {
	string answer;
public:
	friend class User;
	friend class System;
	friend class base;
	Answer() {};
	Answer(string answers, int Id, int FRom_id, int tO_id) {
		this->answer = answers;
		this->ID = Id;
		this->From_ID = FRom_id;
		this->To_ID = tO_id;
	}
};
vector<Answer>answer_save;
class User {
public:
	friend class Answer;
	friend class Question;
	string User_Name;
	string Password;
	int User_ID;
	User() {};
	User(string user_name, string password, int user_id) {
		this->User_Name = user_name;
		this->Password = password;
		this->User_ID = user_id;
	}

	int Ask_question() {
		cout << "Enter username or -1 to return menu:\n";
		string user_s; cin >> user_s; int id_s = 0;
		if (user_s == "-1") { return -1; }
		else {
			for (int i = 0; i < user_save.size(); i++) {
				if (user_s == user_save[i].User_Name) {
					id_s = user_save[i].User_ID;
				}
			}
			if (id_s == 0) {
				cout << "the username is wrong ,please try again...\n";
				return Ask_question();
			}
			cout << "Enter question text:\n";
			string text; cin >> std::ws; getline(cin, text);
			int qustions_id = 0;
			if (questions_save.empty()) {
				qustions_id = 1;
			}
			else {
				qustions_id = questions_save.back().ID + 1;
			}
			questions_save.push_back({ text,qustions_id,User_ID,id_s });
			cout << "If you want add new question enter 1 or if you want return menu enter 2\n";
			int ope; cin >> ope;
			if (ope == 1) { return Ask_question(); }
			return 1;
		}
	}

	int Add_Answer() {
		cout << "Enter question id or -1 to return menu:\n";
		int questions_ip; cin >> questions_ip;
		if (questions_ip == -1) { return -1; }
		else {
			bool flag = 0; string QUESTION, ANSWER; int ip_from, ip_to;
			for (int i = 0; i < questions_save.size(); i++) {
				if (questions_ip == questions_save[i].ID) {
					flag = 1;
					QUESTION = questions_save[i].quesion;
					ip_from = questions_save[i].To_ID;
					ip_to = questions_save[i].ID;

				}

			}
			if (!flag) {
				cout << "the id is wrong ,please try again...\n";
				return Add_Answer();
			}
			else {
				bool cheak = 0; string Answered;
				cout << "Question ID (" << questions_ip << ") from user id (" << ip_to << ")" << "			" << "Question: " << QUESTION << endl;

				for (int i = 0; i < answer_save.size(); i++) {
					if (ip_from == answer_save[i].To_ID) {
						cheak = 1; Answered = answer_save[i].answer;
					}
				}
				if (cheak) {
					cout << "Answer:" << Answered << endl;
					cout << "Warning: Already answered. \n";
					return Add_Answer();
				}
				else {
					string ans;
					int ip_ans = 1;
					cout << "Enter you Answer: ";
					cin >> std::ws; getline(cin, ans);
					if (answer_save.empty()) {
						ip_ans = 1;
					}
					else {
						answer_save.back().ID + 1;
					}
					answer_save.push_back({ ans,ip_ans,ip_from,ip_to });
					cout << "Enter 1 to add new answer or any buttom to return menu:\n";
					char ope; cin >> ope;
					if (ope == '1') { return Add_Answer(); }
					else { return -1; }
				}
			}
		}
	}

	int Delet_question() {
		cout << "Enter id question to answer or -1 return menu\n";
		int ib_que; cin >> ib_que; if (ib_que == -1) { return -1; }
		else {
			vector<Question>temp_que;
			vector<Answer>temp_ans;
			int temp_id = -1;
			for (int i = 0; i < questions_save.size(); i++) {
				if (ib_que == questions_save[i].ID) { temp_id = questions_save[i].From_ID; continue; }
				else {
					temp_que.push_back({ questions_save[i] });

				}

			}
			for (int j = 0; j < answer_save.size(); j++) {
				if (temp_id == answer_save[j].To_ID) {
					continue;
				}
				else {
					temp_ans.push_back({ answer_save[j] });
				}
			}
			questions_save.clear();
			answer_save.clear();
			for (int i = 0; i < temp_que.size(); i++) {
				questions_save.push_back({ temp_que[i] });
			}
			for (int i = 0; i < temp_ans.size(); i++) {
				answer_save.push_back({ temp_ans[i] });
			}
		}
		cout << "Enter 1 to delet new quesions or any buttom to return menu\n";
		int op; cin >> op; if (op == 1) { return Delet_question(); }
		else {
			return -1;
		}
	}


};


class System {
public:
	friend class User;
	friend class Question;
	friend class Answer;

	int menu() {
		cout << "menu:\n";
		cout << "			1:Login" << endl;
		cout << "			2:Sign Up" << endl;
		int op;
		cout << "Enter number in range 1 - 2: " << endl;
		cin >> op;
		if (op < 1 || op>2) {
			cout << "Invaled number";
			return menu();
		}
		return op;
	}
	User Sign_Up() {
		string user_nam;
		string pass;
		int id_the_user;
		cout << "Enter user name. (No spaces) : \n";
		cin >> user_nam;
		cout << "Enter password : \n";
		cin >> pass;
		for (int i = 0; i < user_save.size(); i++) {
			if (user_nam == user_save[i].User_Name) {
				cout << "This user is already used\n";
				return Sign_Up();
			}
		}
		if (user_save.empty()) {
			id_the_user = 1;
		}
		else {
			id_the_user = user_save.back().User_ID + 1;
		}
		User users = { user_nam ,pass ,id_the_user };
		user_save.push_back(users);
		return users;
	}
	User login() {
		string nmnm, passworde;
		cout << "Enter your user name:\n";
		cin >> nmnm;
		cout << "Enter your password : \n";
		cin >> passworde;
		bool flag = 0;
		for (int i = 0; i < user_save.size(); i++) {
			if (nmnm == user_save[i].User_Name && passworde == user_save[i].Password) {
				return user_save[i];
				flag = 1;
			}
		}
		if (!flag) {
			cout << "Invaled user name ,plesse try again\n";
			cout << "Enter 1 to login or any button to exit\n";
			string op; cin >> op; if (op == "1") { return login(); }
		}
		User Invaled = { "-1","-1",-1 };
		return Invaled;
	}
	int menu2() {
		cout << "Menu:\n";
		cout << "			1: Print Questions To Me" << endl;
		cout << "			2: Print Questions From Me" << endl;
		cout << "			3: Answer Questions " << endl;
		cout << "			4: Delete Questions " << endl;
		cout << "			5: Ask Questions " << endl;
		cout << "			6: List System Users" << endl;
		cout << "			7: Feed" << endl;
		cout << "			8: Logout" << endl;
		int operation;
		cout << "Enter number in range 1 - 8: ";
		cin >> operation;
		if (operation < 1 || operation >8) {
			cout << "Invaled Nember\n";
			return menu2();
		}
		return operation;
	}
	System() {

		ifstream file("user list.txt", ios::in);
		if (file.fail()) {
			cout << "faild download users data" << endl;
			return;
		}
		user_save.clear();
		if (!file.fail()) {
			User odj;
			while (file >> odj.User_Name >> odj.Password >> odj.User_ID) {
				user_save.push_back(odj);
			}
			file.close();
		}


		ifstream file1("questions list.txt", ios::in);
		if (file1.fail()) {
			cout << "faild download questions data" << endl;
			return;
		}
		questions_save.clear();
		if (!file1.fail()) {
			Question asd;
			while (file1 >> asd.quesion >> asd.ID >> asd.From_ID >> asd.To_ID) {
				questions_save.push_back(asd);
			}
			file1.close();
		}



		ifstream file2("Answer list.txt", ios::in);
		if (file2.fail()) {
			cout << "faild download Answer data" << endl;
			return;
		}
		answer_save.clear();
		if (!file2.fail()) {
			Answer dsa;
			while (file2 >> dsa.answer >> dsa.ID >> dsa.From_ID >> dsa.To_ID) {
				answer_save.push_back(dsa);
			}
			file2.close();
		}

	}
	~System() {
		ofstream file("user list.txt", ios::out);
		if (file.fail()) {
			cout << "faild download users data" << endl;
			return;
		}
		for (int i = 0; i < user_save.size(); i++) {
			User odj = user_save[i];
			file << odj.User_Name + '\n' << odj.Password + '\n' << (odj.User_ID - 10) + '\n';
		}
		file.close();


		ofstream file1("questions list.txt", ios::out);
		if (file1.fail()) {
			cout << "faild download questions data" << endl;
			return;
		}
		for (int i = 0; i < questions_save.size(); i++) {
			Question asd = questions_save[i];
			file1 << asd.quesion << '\n' << asd.ID << '\n' << asd.From_ID << '\n' << asd.To_ID << '\n';
		}
		file1.close();


		ofstream file2("Answer list.txt", ios::out);
		if (file2.fail()) {
			cout << "faild download answer data" << endl;
			return;
		}
		for (int i = 0; i < answer_save.size(); i++) {
			Answer dsa = answer_save[i];
			file2 << dsa.answer << '\n' << dsa.ID << '\n' << dsa.From_ID << '\n' << dsa.To_ID << '\n';
		}
		file2.close();
	}

	void Print_Questions_to_me(User uu) {
		if (questions_save.empty()) {
			cout << "not found questions. ";

		}
		else {
			bool cheak = 0;
			for (int i = 0; i < questions_save.size(); i++) {
				if (uu.User_ID == questions_save[i].To_ID) {
					cheak = 1;
				}
			}
			if (!cheak) {
				cout << "not fount question from this user\n";
			}
			else {
				for (int i = 0; i < questions_save.size(); i++) {
					if (uu.User_ID == questions_save[i].To_ID) {
						bool flag = 0; string ans;
						for (int j = 0; j < answer_save.size(); j++) {
							if (answer_save[j].From_ID == questions_save[i].To_ID) {
								flag = 1;
								ans = answer_save[j].answer;
							}
						}
						if (flag) {
							cout << "Questions (" << questions_save[i].ID << ") : " << questions_save[i].quesion << endl;
							cout << "Answer:" << ans << endl;
						}
						else {
							cout << "Questions (" << questions_save[i].ID << ") : " << questions_save[i].quesion << endl;
						}
					}
				}

			}

		}
	}

	void Print_quesions_from_me(User user) {
		if (questions_save.empty()) {
			cout << "not found any questions. ";
		}

		else {
			bool cheak = 0;
			for (int i = 0; i < questions_save.size(); i++) {
				if (user.User_ID == questions_save[i].From_ID) {
					cheak = 1;
				}
			}
			if (!cheak) {
				cout << "not fount question from this user\n";
			}
			else {
				for (int i = 0; i < questions_save.size(); i++) {
					if (user.User_ID == questions_save[i].From_ID) {
						bool flag = 0; string ans;
						for (int j = 0; j < answer_save.size(); j++) {
							if (answer_save[j].To_ID == questions_save[i].From_ID) {
								flag = 1;
								ans = answer_save[j].answer;
							}
						}
						if (flag) {
							cout << "Questions (" << questions_save[i].ID << ") : " << questions_save[i].quesion << endl;
							cout << "Answer:" << ans << endl;
						}
						else {
							cout << "Questions (" << questions_save[i].ID << ") : " << questions_save[i].quesion << endl;
							cout << "not found answer" << endl;
						}
					}
				}

			}

		}

	}

	void Listing_system_users() {
		for (int i = 0; i < user_save.size(); i++) {
			cout << "ID: " << user_save[i].User_ID << "			" << "Name:" << user_save[i].User_Name << endl;
		}

	}

	void Feed() {
		if (questions_save.empty()) {
			cout << "not found any questions. ";
		}
		else {
			for (int i = 0; i < questions_save.size(); i++) {
				bool flag = 0; string ans;
				for (int j = 0; j < answer_save.size(); j++) {
					if (answer_save[j].To_ID == questions_save[i].ID) {
						flag = 1; ans = answer_save[j].answer;
					}
				}
				if (flag) {
					cout << "Questions (" << questions_save[i].ID << ") : " << questions_save[i].quesion << endl;
					cout << "Answer:" << ans << endl;
				}
				else {
					cout << "Questions (" << questions_save[i].ID << ") : " << questions_save[i].quesion << endl;
				}

			}
		}
	}


};













int main() {

	User user_new;
	int op;
restart:
	System sys;
	op = sys.menu();
	if (op == 2) {
		user_new = sys.Sign_Up();
	}

	if (op == 1) {
		user_new = sys.login();
		if (user_new.User_ID == -1) { return 0; }
	}

	cout << "Hello " << user_new.User_Name << endl;
start:
	op = sys.menu2();

	if (op == 1) {
		sys.Print_Questions_to_me(user_new);
		goto start;
	}

	if (op == 2) {
		sys.Print_quesions_from_me(user_new);
		goto start;
	}
	if (op == 3) {
		user_new.Add_Answer();
		goto start;
	}
	if (op == 4) {
		user_new.Delet_question();
		goto start;
	}

	if (op == 5) {
		user_new.Ask_question();
		goto start;
	}

	if (op == 6) {
		sys.Listing_system_users();
		goto start;
	}

	if (op == 7) {
		sys.Feed();
		goto start;
	}
	if (op == 8) {

		int ope;
		cout << "Enter 1 to end programme or 2 to enter another user\n";
		cin >> ope;
		if (ope == 1) { return 0; }
		if (ope == 2) { goto restart; }

	}
}
