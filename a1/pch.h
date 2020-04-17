//HaoranCheng 5044194

#ifndef PCH_H
#define PCH_H

#include<string>
#include <fstream>
#include "vector"
using namespace std;

void get_input(char* argv[]);

vector<string>split(string str, string separator);

int read_data(const char * fname);

struct Animals
{
	string name;
	string type;
	string registration;
	int problem;
};

struct Vets
{
	string name;
	int quality;
};

struct Problems
{
	string name;
	int problem_determination_complexity;
	int problem_treatment_complexity;
	int treatment;
};

struct Treatments
{
        string name;
};

struct Results
{
        string vet;
        string animal;
        string actual_problem;
        string diagnose_problem;
        string applied_treatment;
        string is_works;
};

void create_animal(vector<string> list);

void create_vet(vector<string> list);

void create_problem(vector<string> list);

void create_treatment(vector<string> list);

void initial_detect();

void process_diagnose(Animals a);

int random_choose(int r);

int get_correct_problem(Animals a);

int get_treatment(int problem);

double calc_chance(int quality, int complexity);

int process_determination(double chance, int correct_determination);

int simu_diagnose(double chance, int correct_determination);

int guess();

double calc_working_chance(int applied_treatment,int correct_treatment,double chance);

string simu_treatment(int working_chance);

void print(string animal, string vet,string coorrect_problem, string diagnose_problem, string treatment, string w);

void output_results();

#endif
