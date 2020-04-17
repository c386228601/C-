//HaoranCheng 5044194

#include "pch.h"
#include "time.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>
#include <string>
#include "vector"
#define random(a,b)(rand()%(b-a+1)+a)

int limit;
char *output_file;
Animals alist[20];
Vets vlist[10];
Problems plist[20];
Treatments tlist[20];
Results rlist[20];


void get_input(char* argv[])
{
        //get the number of animal we need 
        limit = atoi(argv[1]);

        //get the file names
        for(int i = 2; i < 6;i++)
        {
           read_data(argv[i]);
        }
        
       //the file name which we want to output into
        output_file = argv[6];
}


//process the file data
int read_data(const char* fname)
{
          fstream f;

          char content[30];

          string filename = fname;

          vector<string> v;

          cout << filename << endl;

          int count = 0;

          f.open(fname,ios::in);
          //if cannot open file   
          if(!f)
          {
             cerr << "Error opening: " << filename << endl;
             return -1;
          }
          f.getline(content, 30,'.');
          
           while( ! f.eof())
           {
             v = split(content,":");
             //if invalid characters rising error
             if(f.fail())
             {
                  f.clear(); 
                  f.ignore(100,'\n');
             }
             //if hardware problems 
             if(f.bad())
             {
                 return -2;
             }

             if(filename == "Animals.txt" && count < limit)
             {
                 create_animal(v);
                 cout << content;
                 count++;
             }
             if(filename == "Vets.txt")
             {
                 create_vet(v);
                 cout << content;
             }
             if(filename == "Problems.txt")
             {
                 create_problem(v);
                 cout << content;

             }
             if(filename == "Treatments.txt")
             {
                 create_treatment(v);
                 cout << content;
             }
            f.getline(content, 100,'.');
          }
            f.close();
           cout <<"\n"<< endl;
}

//split the data by ':'
vector<string> split(string str,string separator)
{
        vector<string> result;
        int cutAt;  
        while((cutAt = str.find_first_of(separator))!=str.npos)
        {
                if(cutAt>0)
                {
                        result.push_back(str.substr(0,cutAt));
                }
                str=str.substr(cutAt+1);  
        }
        if(str.length()>0)
        {  
                result.push_back(str);
        }  
        return result;
}


//start create the structs
int i_1 = 0;
void create_animal (vector<string> list)
{

        Animals a;
     
        a.name = list[0];

        a.type = list[1];

        a.registration = list[2];

        a.problem = atoi(list[3].c_str());

        alist[i_1++] = a;
}

int i_2 = 0;
void create_vet(vector<string> list)
{
       Vets v;
       v.name = list[0];
       v.quality = atoi(list[1].c_str());
       vlist[i_2++] = v;
}

int i_3 = 0;
void create_problem(vector<string> list)
{
       Problems p;
       p.name = list[0];
       p.problem_determination_complexity = atoi(list[1].c_str());
       p.problem_treatment_complexity = atoi(list[2].c_str());
       p.treatment = atoi(list[3].c_str());
       plist[i_3++] = p;
}

int i_4 = 0;
void create_treatment(vector<string> list)
{
       Treatments t;
       t.name = list[0];
       tlist[i_4++] = t;
}
//end create structs

//intial the detect
void initial_detect()
{
        srand((unsigned)time(NULL));
        cout<<"----------diagnose process----------"<<endl;
        for(int i = 0; i < i_1; i ++)
        {
            process_diagnose(alist[i]);
			
        }

}

//put the animals into detect process one by one
void process_diagnose(Animals a)
{
          int r;
	  int correct_problem;
	  int correct_treatment;
	  double chance;
	  int problem_determination;
	  int treatment_determination;
	  int applied_treatment;
	  int working_chance;
	  string working_result;
	
          //random choose a vet for animal   
          r = random_choose(i_2);
 
	  //get the actual problem
	  correct_problem = get_correct_problem(a);

          //calculate diagnose chance 
          chance = calc_chance(vlist[r].quality,plist[correct_problem].problem_determination_complexity);
	  
          //determinte the problem
	  problem_determination = process_determination(chance, correct_problem);
	  
          //applied the treatment for the determinted problem
	  applied_treatment = get_treatment(problem_determination);
	  
          //get the correct treatment
          correct_treatment = get_treatment(correct_problem);
	  
          //calculate treatment chance
          chance = calc_chance(vlist[r].quality,plist[correct_treatment].problem_treatment_complexity);
	  
          //calculate working successful chance
          working_chance = calc_working_chance(applied_treatment,correct_treatment,chance);
	  
          //return the working results
          working_result = simu_treatment(working_chance);
      
          //print the whloe detect process and add the records into a list for output
          print(a.name, vlist[r].name,plist[correct_problem].name,plist[problem_determination].name, tlist[applied_treatment].name,working_result); 

}

//common function for generating a random number
int random_choose(int r)
{
	return random(0,r-1);	
}

//get the problem
int get_correct_problem(Animals a)
{
	return a.problem - 1;
}

//get treatment
int get_treatment(int problem)
{
	return plist[problem].treatment - 1;
}

//common fuinction for calculate chance
double calc_chance(int quality, int complexity)
{
      double chance = 50+(quality - complexity)/2.5;
      
      return chance;	  
}

//start determinate problem
int process_determination(double chance, int correct_determination)
{
      //if chance greater than 100% return correct problem
      if(chance >= 100)
      {
          return correct_determination;
      }
      //else simulate diagonse according to the successful chance
      else
      {
         return simu_diagnose(chance, correct_determination);
      }
}

int simu_diagnose(double chance,int correct_determination)
{
        //random choose a number within 0 - 100
        int r = random_choose(100);
        //if this number under the successful chance
        if(r <= chance)
	{
		return correct_determination;
	}
	else
	{
         //else determination false start guess
		return guess();
	}
}  

int guess()
{
	return random_choose(i_3);
}

//calculate the treatment working chance
double calc_working_chance(int applied_treatment, int correct_treatment, double chance)
{
        //if the applied treatment equals to the correct treatment
	if(applied_treatment == correct_treatment)
	{
		return chance;
	}
        //else working chance = chance/4 
	else
	{
		return chance * 0.25; 
	}		
}

//simulate the the treatment
string simu_treatment(int working_chance)
{
           int r = random_choose(100);
	   if(r <= working_chance)
	   {
		   return "success";
	   }
	   else
	   {
		   return "false";
	   }
}

//print result
int result_count = 0;

void print(string animal, string vet,string actual_problem,string diagnose_problem, string applied_treatment, string works)
{          
          Results result;
          result.vet = vet;
          result.animal = animal;
          result.diagnose_problem = diagnose_problem;
          result.actual_problem = actual_problem;
          result.applied_treatment = applied_treatment;
          result.is_works = works;
      
          rlist[result_count] = result;

          result_count++;
	  
          cout << "Animal: "<< animal<<endl;
          cout << "Vet: "<< vet << endl;
          cout << "Diagonse problem: "<< diagnose_problem<<endl;
          cout << "Actual problem: "<< actual_problem << endl;
          cout << "Applied treatment: "<< applied_treatment <<endl;
          cout << "Working: " << works << endl;
          cout << endl;
}                         

//output into txt file
void output_results()
{
    ofstream out(output_file);

    for(int i = 0; i < result_count;i++)
    {
       out << "Animal: "<< rlist[i].animal<<endl;
       out << "Vet: "<< rlist[i].vet << endl;
       out << "Diagonse problem: "<< rlist[i].diagnose_problem<<endl;
       out << "Actual problem: "<< rlist[i].actual_problem << endl;
       out << "Applied treatment: "<< rlist[i].applied_treatment <<endl;
       out << "Working: " << rlist[i].is_works << endl;
       out << endl;
    }
       out.close();
}
