#include <iostream>
#include <climits>
#include <string>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;
vector<vector<int>> leerFichero(string nombre,int &n, int &m) {
    ifstream fich(nombre);

    fich >> n >> m;  

    vector<vector<int>> laberinto(n, vector<int>(m));  

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fich>> laberinto[i][j];  
        }
    }

    return laberinto;
}
int maze_greedy(vector<vector<int>>& maze,vector<vector<int>>& path) {
    int n = maze.size();
    int m = maze[0].size();
    int i = 0;
    int j = 0;
    int suma = 0;
    if(maze[0][0] == 0){
        return 0;
    }
    suma+= 1;
    path[0][0] = -1;
    while(i<n -1 || j < m-1){
        if((i+1 < n && j+1 < m) && maze[i+1][j+1]== 1){
            i++;
            j++;
            suma += 1;
            path[i][j]= -1;
        }else{
            if((i+1 < n-1) && maze[i+1][j] == 1){
                i++;
                suma += 1;
                path[i][j] = -1;
            }else if((j+1 < m-1) && maze[i][j+1]==1){
                j++;
                suma += 1;
                path[i][j]=-1;
            }else{
                if(i+1 < n-1 && j+1  < m-1){
                    suma = 0;
                    return suma;
                }else{
                    if(maze[n-1][m-1] != 0){
                        if(n!=1 || m != 1){
                            suma+= 1;
                        }

                        path[n-1][m-1] = -1;
                    }else{
                        suma = 0;
                    }
                    return suma;

                }
            }
        }
    }
    return suma;

}
void maze_parser(vector<vector<int>> path){
    for(auto aux: path){
        for(int v: aux){
            if(v == -1)
                cout << "*" << ' ';
            else
                cout << v << ' ';
        }
        cout << endl;
    }  

}
int main(int argc, char* argv[]){
    bool p = false;

    bool comprobar = false;
    string nombre = "";
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i],"-f")==0){
            if(i < argc -1){
                nombre = argv[i+1];
                comprobar = true;
                i++;
            }else{
                cerr << "ERROR: missing filename." << endl
                << "Usage: " << endl
                << "maze_greedy [-p] [-t] [--ignore-naive] -f file" << endl;
                exit(EXIT_FAILURE);               
            }

        }else if(strcmp(argv[i],"-p")== 0){
            p = true;
        }else{
                cerr << "ERROR: unknown option " << argv[i] << "."<< endl
                << "Usage: " << endl
                << "maze_greedy [-p] [-t] [--ignore-naive] -f file" << endl;
                exit(EXIT_FAILURE); 
        }
    }
    if(comprobar == false || nombre ==""){
                cerr << "Usage: " << endl
                << "maze_greedy [-p] -f file" << endl;
                exit(EXIT_FAILURE);  
    }
    ifstream fich(nombre);
    if(!fich.is_open()){
                cerr << "ERROR: can't open file: " << nombre << "." << endl
                << "Usage: " << endl
                << "maze_greedy [-p] [-t] [--ignore-naive] -f file" << endl;
                exit(EXIT_FAILURE);  
    }
    fich.close();
    
    int n= 0;
    int m= 0;
    int suma = 0;
    vector<vector<int>> laberinto = leerFichero(nombre,n,m);
    vector<vector<int>>& path = laberinto;
    suma = maze_greedy(laberinto,path);
    cout << suma << endl;
    if(p == true){
        maze_parser(path);
    }

}