#include <iostream>
#include <climits>
#include <string>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

int maze_naive(vector<vector<int>>& maze, unsigned r, unsigned c) {
  if(maze.size()-1 == r && maze[0].size()-1 == c-1){
    return 0;
  }
   if(r>= maze.size() || c >= maze[0].size() || maze[r][c] == 0) { 
        return INT_MAX-1;
    }
    maze[r][c] = 0;

    int right = maze_naive(maze, r, c+1);
    int down = maze_naive(maze, r+1, c);
    int diagonal = maze_naive(maze, r+1, c+1);

    maze[r][c] = 1;

    
    return min(diagonal, min(right, down)) + 1;
}
int maze_memo(vector<vector<int>> matriz, unsigned r, unsigned c, vector<vector<int>>& memo) {
    int n = matriz.size();
    int m = matriz[0].size();
    int caminoCorto = INT_MAX -10;

    if(n-1 == r && m-1 == c){
        memo[r][c] = 1;
        return 1;
    }
    if(r>= n || c >= m || matriz[r][c] == 0) { 
        return caminoCorto;
    }

    if (c + 1 < m && matriz[r][c + 1] == 1) {
        if(memo[r][c+1] == -1){
            caminoCorto = min(caminoCorto, 1 + maze_memo(matriz, r, c + 1, memo));
        }else{
            caminoCorto = min(caminoCorto, 1+ memo[r][c+1]);
        }
        
    }

    
    if (r + 1 < n && matriz[r + 1][c] == 1) {
        if(memo[r+1][c] == -1){
            caminoCorto = min(caminoCorto, 1 + maze_memo(matriz, r+1, c, memo));
        }else{
            caminoCorto = min(caminoCorto, 1+ memo[r+1][c]);
        }
    }

   
    if (r + 1 < n && c + 1 < m && matriz[r + 1][c + 1] == 1) {
        if(memo[r+1][c+1] == -1){
            caminoCorto = min(caminoCorto, 1 + maze_memo(matriz, r+1, c + 1, memo));
        }else{
            caminoCorto = min(caminoCorto, 1+ memo[r+1][c+1]);
        }
    }
    memo[r][c] = caminoCorto;
    return caminoCorto;
}
int maze_it_vector(vector<vector<int>> &matriz) {
    int n = matriz.size();
    int m = matriz[0].size();
    vector<vector<int>> aux(n, vector<int>(m, -1));
    int inf = 2 * n * m;
    if (matriz[n-1][m-1] == 0) {
        return 1;
    }
    aux[n-1][m-1] = 1;
        for (int j = m-2; j >= 0; j--) {
        if (matriz[n-1][j] == 1 && aux[n-1][j+1] != -1 && matriz[n-1][j+1] == 1) {
            aux[n-1][j] = aux[n-1][j+1] + 1;
        } else {
            aux[n-1][j] = inf;
        }
    }
    for (int i = n-2; i >= 0; i--) {
        if (matriz[i][m-1] == 1 && aux[i+1][m-1] != -1 && matriz[i+1][m-1] == 1) {
            aux[i][m-1] = aux[i+1][m-1] + 1;
        } else {
            aux[i][m-1] = inf;
        }
    }
    for (int i = n-2; i >= 0; i--) {
        for (int j = m-2; j >= 0; j--) {
            if (matriz[i][j] == 0) {
                aux[i][j] = -2;
            } else {
                int down = inf;
                int right = inf;
                int diagonal = inf;
                if(aux[i+1][j] != -1 && matriz[i+1][j] == 1) {
                    down = aux[i+1][j];
                }

                if(aux[i][j+1] != -1 && matriz[i][j+1] == 1) {
                    right = aux[i][j+1];
                }

                if(aux[i+1][j+1] != -1 && matriz[i+1][j+1] == 1) {
                    diagonal = aux[i+1][j+1];
                }
                
                aux[i][j] = min(diagonal,min(down, right)) + 1;
            }
        }
    }
    return aux[0][0];
}
void maze_parser(vector<vector<int>> map,vector<vector<int>> memo){
    vector<vector<int>> path = map;
    int i = 0;
    int j = 0;
    int right = INT_MAX;
    int down = INT_MAX;
    int diagonal = INT_MAX;
    path[i][j] = -1;
    while(memo[i][j] != 1){
        if(i + 1 <memo.size()-1){
            right = memo[i+1][j];
        }if(j + 1 < memo[0].size()-1){
            down = memo[i][j+1];
        }if(i + 1 <memo.size()-1 && j + 1 < memo[0].size()-1){
            diagonal = memo[i+1][j+1];
        }

        if(right == diagonal && right == down){
            path[i+1][j+1] = -1;
            i++;
            j++;
        }else if(right == diagonal){
            if(right < down){
                path[i+1][j+1] = -1;
                i++;
                j++;               
            }else{
                path[i][j+1] = -1;
                j++;
            }

        }else if(down == diagonal){
            if(down < right){
                path[i+1][j+1] = -1;
                i++;
                j++;                  
            }else{
                path[i+1][j] = -1;
                i++;                  
            }
        }else if(right == down){
            if(right < diagonal){
                path[i][j+1] = -1;
                j++;
            }else{
                path[i+1][j+1]=-1;
                i++;
                j++;
            }

        }else if(diagonal < down){
            if(diagonal < right){
                path[i+1][j+1] = -1;
                i++;
                j++;                
            }else{
                path[i+1][j] = -1;
                i++;
            }
        }else if(down < right){
            path[i][j+1] = -1;
            j++;
        }else{
            path[i+1][j] = -1;
            i++;
        }  
    }
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

void printMatrix(vector<vector<int>> matrix){

    for(auto aux: matrix){
        for(int v: aux){
            if(INT_MAX - 15 < v)
                cout << 'X' << ' ';
            else if(v == -1)
                cout << '-' << ' ';
            else
                cout << v << ' ';
        }
        cout << endl;
    }
}


int main(int argc, char* argv[]){
    
    bool p = false;
    bool t = false;
    bool naive = false;

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
                << "maze [-p] [-t] [--ignore-naive] -f file" << endl;
                exit(EXIT_FAILURE);               
            }
 
        }else if(strcmp(argv[i],"-t")== 0){
            t = true;
        }else if(strcmp(argv[i],"-p")== 0){
            p = true;
        }else if(strcmp(argv[i],"--ignore-naive")== 0){
            naive = true;
        }else{
                cerr << "ERROR: unknown option." << endl
                << "Usage: " << endl
                << "maze [-p] [-t] [--ignore-naive] -f file" << endl;
                exit(EXIT_FAILURE); 
        }
    }
    if(comprobar == false || nombre ==""){
                cerr << "Usage: " << endl
                << "maze [-p] [-t] [--ignore-naive] -f file" << endl;
                exit(EXIT_FAILURE);  
    }
    ifstream fich(nombre);
    if(!fich.is_open()){
                cerr << "ERROR: unable to open the file." << endl
                << "Usage: " << endl
                << "maze [-p] [-t] [--ignore-naive] -f file" << endl;
                exit(EXIT_FAILURE);  
    }
    fich.close();
    
    
    // AQUI ACABA LA COMPRobacion
    
    int n= 0;
    int m= 0;
    vector<vector<int>> laberinto = leerFichero(nombre,n,m);


    vector<vector<int>> memo = vector<vector<int>>();
    for(int i = 0;i <laberinto.size();i++){
        memo.push_back(vector<int>(laberinto[0].size(),-1));
    }
    if(naive == true){
        cout << "-" << " " << maze_memo(laberinto,0,0,memo) << " " << maze_it_vector(laberinto) << endl;
    }else{
        cout << maze_naive(laberinto,0,0) << " " << maze_memo(laberinto, 0, 0, memo) << " " << maze_it_vector(laberinto) << endl;
        if(p == true){
            maze_parser(laberinto,memo);
        }else if(t == true){
            cout << "Memoization table:" <<endl;
            printMatrix(memo);
        }
    }
    


}
