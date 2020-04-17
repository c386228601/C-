//Haoran Cheng 5044194

#include "A3.h"
#include <fstream>
#include <iostream>
#include <ctype.h>

int main(int argc, char* argv[])
{
             
	read_file(argv[1],argv[2],argv[3]);
	output_file(argv[1],argv[2],argv[4]);
}

//read files
void read_file(string from,string to,const char* filename)
{
	ifstream inFile;
	string to_string;
	string m;
	char l;
	char b[7] = "";
	int times = 0;
	
	inFile.open(filename);
      if(inFile.fail()){cout<<"invalid character";}//invalid character
      if(inFile.bad()){cout<<"hardware failure";}// hardware failure
	if (from == "Morse")
	{
        inFile >> m;
		while (!inFile.eof())
		{
			to_string = m;
			Morse _morse(to_string);
			morse_list.push(_morse);
			_morse.trans(to);
                        inFile >> m;
		}
	}
	if (from == "Braille")
	{
		while (!inFile.eof())
		{
			if (times <= 5)
			{
		           inFile >> b[times];                                
			}
			if(times > 5)
			{
                to_string = b;
                Braille _braille(to_string);

				times = 0;
				inFile >> b[times];
				braille_list.push(_braille);
				_braille.trans(to);                            
			}
                     times++;
		}
	}
	if (from == "Latin")
	{
		while (!inFile.eof())
		{
			inFile >> l;
			if(isupper(l))
			{
				cout<<"Not supper Upper case"<<endl;
				break;	
			}
			to_string = l;
			Latin _latin(to_string);
			latin_list.push(_latin);
			_latin.trans(to);
		}
	}
       inFile.close();
}

//output files and show results
void output_file(string from, string to, const char* fname)
{
      Morse m("");
      Braille b("");
      Latin l(""); 
      if(from == "Latin" && to == "Morse")
           {  
	   			   //show translating rules
             l.show_mrule();                   
             cout<<"source: ";
		     latin_list.pop();
             cout<<"target: ";
		     morse_list.pop();
		     morse_list.out(fname);
           }

           if(from == "Latin" && to == "Braille")
           {
			   			   //show translating rules
             l.show_brule();
              cout<<"source: ";
		     latin_list.pop();
              cout<<"target: ";
		     braille_list.pop();
	         braille_list.out(fname);
           }

           if(from == "Morse" && to == "Latin")
           {
                     m.show_lrule();
                     cout<<"source: ";
		     morse_list.pop();
                     cout<<"target: ";
      		     latin_list.pop();
		     latin_list.out(fname);
           }

           if(from == "Morse" && to == "Braille")
           {
			   //show translating rules
                     m.show_lrule();
                     l.show_brule();
                     cout<<"source: ";
					 //show resules
		     morse_list.pop();
                     cout<<"intermediate: ";
		     latin_list.pop();
                     cout<<"target: ";
		     braille_list.pop();
			 //output results into txt
		     braille_list.out(fname);
           }

           if(from == "Braille" && to == "Morse")
           {
			   			   //show translating rules
                     b.show_lrule();
                     l.show_mrule();
                     cout<<"source: ";
		     braille_list.pop();
                     cout<<"intermediate: ";
		     latin_list.pop();
                     cout<<"target: ";
		     morse_list.pop();
		     morse_list.out(fname);
           }

           if(from == "Braille" && to == "Latin")
           {
			   			   //show translating rules
                     b.show_lrule();
                     cout<<"source: ";
		     braille_list.pop();
                     cout<<"target: ";
		     latin_list.pop();
	             latin_list.out(fname);		   
           }
}

Morse::Morse(string m)
{ 
  source = m;
  latin_map["----"] = " ";       
  latin_map[".-"] = "a";
  latin_map["-..."] = "b";
  latin_map["-.-."] = "c";
  latin_map["-.."] = "d";
  latin_map["."] = "e";
  latin_map["..-."] = "f";
  latin_map["--."] = "g";
  latin_map["...."] = "h";
  latin_map[".."] = "i";
  latin_map[".---"] = "j";
  latin_map["-.-"] = "k";
  latin_map[".-.."] = "l";
  latin_map["--"] = "m";
  latin_map["-."] = "n";
  latin_map["---"] = "o";
  latin_map[".--."] = "p";
  latin_map["--.-"] = "q";
  latin_map[".-."] = "r";
  latin_map["..."] = "s";
  latin_map["-"] = "t";
  latin_map["..-"] = "u";
  latin_map["...-"] = "v";
  latin_map[".--"] = "w";
  latin_map["-..-"] = "x";
  latin_map["-.--"] = "y";
  latin_map["--.."] = "x";
};
Morse::Morse(){};

void Morse::trans(string to)
{
		Latin l(latin_map[source]);
		latin_list.push(l);
		if(to == "Braille")
		{
		   l.trans(to);
		}
}

void Morse::show_lrule()
{
    it = latin_map.begin();

   while(it != latin_map.end())
   {
    cout<<it->first <<" "<<it->second << endl;
    it ++;
    }

}


Braille::Braille(string b)
{
   source = b;
   latin_map["000000"] = " ";
   latin_map["100000"] = "a";
   latin_map["101000"] = "b";
   latin_map["110000"] = "c";
   latin_map["110100"] = "d";
   latin_map["100100"] = "e";
   latin_map["111000"] = "f";
   latin_map["111100"] = "g";
   latin_map["101100"] = "h";
   latin_map["011000"] = "i";
   latin_map["011100"] = "j";
   latin_map["100010"] = "k";
   latin_map["101010"] = "l";
   latin_map["110010"] = "m";
   latin_map["110110"] = "n";
   latin_map["100110"] = "o";
   latin_map["111010"] = "p";
   latin_map["111110"] = "q";
   latin_map["101110"] = "r";
   latin_map["011010"] = "s";
   latin_map["011110"] = "t";
   latin_map["100011"] = "u";
   latin_map["101011"] = "v";
   latin_map["011101"] = "w";
   latin_map["110011"] = "x";
   latin_map["110111"] = "y";
   latin_map["100111"] = "z";


};
Braille::Braille(){};
void Braille::trans(string to)
{
		Latin l(latin_map[source]);
		latin_list.push(l);
		if(to =="Morse")
		{
		   l.trans(to);
		}
}

void Braille::show_lrule()
{
    it = latin_map.begin();

   while(it != latin_map.end())
   {
    cout<<it->first <<" "<<it->second << endl;
    it ++;         
    }

}

Latin::Latin(string l)
{
   source = l;
   braille_map[" "] = "000000";
   braille_map["a"] = "100000";
   braille_map["b"] = "101000";
   braille_map["c"] = "110000";
   braille_map["d"] = "110100";
   braille_map["e"] = "100100";
   braille_map["f"] = "111000";
   braille_map["g"] = "111100";
   braille_map["h"] = "101100";
   braille_map["i"] = "011000";
   braille_map["j"] = "011100";
   braille_map["k"] = "100010";
   braille_map["l"] = "101010";
   braille_map["m"] = "110010";
   braille_map["n"] = "110110";
   braille_map["o"] = "100110";
   braille_map["p"] = "111010";
   braille_map["q"] = "111110";
   braille_map["r"] = "101110";
   braille_map["s"] = "011010";
   braille_map["t"] = "011110";
   braille_map["u"] = "100011";
   braille_map["v"] = "101011";
   braille_map["w"] = "011101";
   braille_map["x"] = "110011";
   braille_map["y"] = "110111";
   braille_map["z"] = "100111"; 
   morse_map[" "] = "----";       
   morse_map["a"] = ".-";
   morse_map["b"] = "-...";
   morse_map["c"] = "-.-.";
   morse_map["d"] = "-..";
   morse_map["e"] = ".";
   morse_map["f"] = "..-.";
   morse_map["g"] = "--.";
   morse_map["h"] = "....";
   morse_map["i"] = "..";
   morse_map["j"] = ".---";
   morse_map["k"] = "-.-";
   morse_map["l"] = ".-..";
   morse_map["m"] = "--";
   morse_map["n"] = "-.";
   morse_map["o"] = "---";
   morse_map["p"] = ".--.";
   morse_map["q"] = "--.-";
   morse_map["r"] = ".-.";
   morse_map["s"] = "...";
   morse_map["t"] = "-";
   morse_map["u"] = "..-";
   morse_map["v"] = "...-";
   morse_map["w"] = ".--";
   morse_map["x"] = "-..-";
   morse_map["y"] = "-.--";
   morse_map["x"] = "--..";

};
Latin::Latin(){};
void Latin::trans(string to)
{
	if (to == "Braille")
	{
		Braille b(braille_map[source]);
		braille_list.push(b);
	}
	if(to == "Morse")
	{
		Morse m(morse_map[source]);
		morse_list.push(m);
	}
}

void Latin::show_mrule()
{
    it = morse_map.begin();

   while(it != morse_map.end())
   {
    cout<<it->first <<" "<<it->second << endl;
    it ++;
    }

}


void Latin::show_brule()
{
    it = braille_map.begin();

   while(it != braille_map.end())
   {
    cout<<it->first <<" "<<it->second << endl;
    it ++;
    }

}


template<class T>
Array<T>::Array(unsigned int _length)
{
     this-> length = _length;
     index = 0;
     objlist = new T [_length];
};

template<class T>
Array<T>::~Array()
{
   delete []objlist;
}


//add obj into array
template<class T>
void Array<T>::push(T obj)
{
   objlist[index++] = obj; 
}


//get obj from array
template<class T>
void Array<T>::pop()
{
    for(int i = 0; i < index;i++)
    {
       cout << objlist[i].source;
    }
   cout << ""<< endl;
}

//output obj to txt
template<class T>
void Array<T>::out(const char*  fname)
{
    ofstream output(fname);
    for(int i = 0; i < index;i++)
    {
       output << objlist[i].source;
    }
   output.close();
  
}
