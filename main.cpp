#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

map <string, map <string,double> > ezer(map <string, map <string,double>>& map1,map <string, map <string,double> >& map2);
void func_for_fill_the_deep_map( map<string,double>& main_map, map <string, map <string,double>>& map1, string word);
void func_fill_the_fathers(map<string,double>& main_map, map<string, map <string,double>>& map2, string father);

int main(){
    string s;
    ifstream ifs{"units.txt"};
//    ifs.open("units.txt");
    map <string,map <string,double>> sizes;
    map <string,map <string,double>> sizes_rev;
    // sizes["gilad"] = "3" ;
   // std::cout << sizes["gilad"] ;

    int s1;
    double s2;
    string word1,word2;
    char c;
    int i=1;
    while(ifs >> s1 >> word1 >> c >> s2 >> word2){
    // cout <<"unit: "<< word1 << "\t=\t" << s2 << " unit2: " << word2 << endl;
    sizes[word1][word2] = s2;
    sizes_rev[word2][word1] = 1/s2;
    }
    map <string, map <string,double> > changes;
    changes = ezer(sizes,sizes_rev);
    
    //prints map
    map <string, map<string,double>>::iterator itr1;
    map <string,double>::iterator deep_itr;
    for (itr1 = changes.begin(); itr1 != changes.end(); itr1++)
    {
        cout << itr1->first;
        for (deep_itr = changes[itr1->first].begin(); deep_itr != changes[itr1->first].end(); deep_itr++)
        {
            std::cout << " <" <<deep_itr->first << ','<<deep_itr->second << "> ";
        }
        cout<<endl;
    }
    return 0;
}

typedef map<string, map<string,double>> Map;

Map ezer(Map& map1,Map& map2){
    Map result;
    Map::iterator itr1,start_itr;
    map<string,double>::iterator itr2;
    // map["km"]["km"] = 1.
    for (start_itr = map1.begin(); start_itr != map1.end(); start_itr++){//"kg" <"kg",1>
        result[start_itr ->first][start_itr ->first] =1.0;
    }
    for (start_itr = map2.begin(); start_itr != map2.end(); start_itr++){//"kg" <"kg",1>
        result[start_itr ->first][start_itr ->first] =1.0;
    }

    for (itr1 = map1.begin(); itr1 != map1.end(); itr1++){
        for(itr2 = map1[itr1 ->first].begin(); itr2 != map1[itr1 -> first].end(); itr2++ ){//for the deep map
            string word1 = itr1 -> first, word2 = itr2 -> first;
            result[itr1 -> first][itr2 ->first] = itr2 -> second; // "km",(<"m",1000>,<"cm",100000>)
            // gets map, map(map), string key
            // insert to the map the all friends with the string key
            // and does that again recirsivly 
            func_for_fill_the_deep_map(result[itr1 ->first], map1, word2);
        }
        // gets map, map(map), string key
        // insert to the map the values mmap
        // and does that recursivly
        func_fill_the_fathers(result[itr1->first], map2, itr1->first);
    }

    for (itr1 = map2.begin(); itr1 != map2.end(); itr1++){
        for(itr2 = map2[itr1 ->first].begin(); itr2 != map2[itr1 -> first].end(); itr2++ ){//for the deep map
            string word1 = itr1 -> first, word2 = itr2 -> first;
            result[itr1 -> first][itr2 ->first] = itr2 -> second; // "km",(<"m",1000>,<"cm",100000>)
            // gets map, map(map), string key
            // insert to the map the all friends with the string key
            // and does that again recirsivly 
            func_for_fill_the_deep_map(result[itr1 ->first], map1, word2);
        }
        // gets map, map(map), string key
        // insert to the map the values mmap
        // and does that recursivly
        func_fill_the_fathers(result[itr1->first], map2, itr1->first);
    }

    return result;
}

void func_for_fill_the_deep_map( map<string,double>& main_map, Map& map1, string word){
    map<string,double>::iterator itr;
    for (itr = map1[word].begin(); itr != map1[word].end(); itr++)
    {
        if(true||main_map.find(itr->first) == main_map.end() ){//if the neighbor not in the new map
            main_map[itr->first] = (itr->second) * (main_map[word]);
            //main_map["cm"] = map1["m"]["cm"](100) * main_map["m"](1000)
            func_for_fill_the_deep_map(main_map, map1, itr->first);
        }
    }
}

void func_fill_the_fathers(map<string,double>& main_map, Map& map2, string father){
    map<string, double>::iterator itr;
    for(itr = map2[father].begin(); itr != map2[father].end(); ++itr){
        if(main_map.find(itr->first) == main_map.end()){
            main_map[itr->first] = itr->second * main_map[father];
            func_fill_the_fathers(main_map, map2, itr->first);
        }
    }
} 

