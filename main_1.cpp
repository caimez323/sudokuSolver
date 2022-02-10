#include <iostream>
#include <vector>
#include <string>
#include <fstream> // pour les lecture-ecriture dans les fichiers

using namespace std;

typedef struct {
  string nom;
  vector<vector<int> > grille;
} Grille;

typedef struct {
  size_t lig;
  size_t col;
} Indices;


// insérer ici les fonctions que vous appelez avant que leurs definitions
// apparaissent dans le fichier
void imprime(const Grille &g); // definie en fin de fichier.



/** Renvoie true si la grille a la bonne forme et ne contient que des valeurs de 0 à 9
 * @param g const Grille& correspond à
 * @return bool correspond à
 */
bool bienFormee(const Grille &g) {
  bool res = true;
  if(g.grille.size() == 9){ //On vérifie d'abord qu'il y a le bon nombre de lignes
    for(size_t t = 0 ;t<g.grille.size();t++ ){//puis on parcourt la ligne en regardant que chaque colonne fait la bonne taille
        if(g.grille.at(t).size() !=9){
            res =false;             //si pour l'une des colonnes ce n'est pas le cas, on renvoie false
        }
    }
  }
  return res;
}

/** on définit une fonction qui nous permet de tester la validité d'un nombre dans la grille
 * @param n un entier
 * @return true si n est compris entre 1 et 9 false sinon.
 */

bool comprisEntre1et9(int n){
    if (n>0 && n<10){
        return true;
    }
return false;
}

/* Verifie si la grille est valide: chaque valeur de 1 à 9 apparait au plus
 * une fois dans chque ligne, colonne et région
 */

 /** cette fonction divise une grille en petite région en fonction de bornes définies
  * @param iD un entier qui sert a parcourir les lignes
  * @param jD un entier qui sert a parcourir les colonnes
  * @param grille un vecteur correspondant a la grille du sudoku
  * @return NewVector correspondant a un vecteur qui correspond a une region de la grille
  *
  */

vector<int> DivisRegion(int iD, int jD, vector<vector<int> > grille){
    vector<int> NewVector (9);
    int iDP = iD +3;
    int jDP = jD +3;
       for(int i =iD; i<iDP;i++){
            for(int j =jD; j<jDP;j++){
                NewVector.push_back(grille.at(i).at(j));
        }
    }
return NewVector;
}

/** cette fonction vérifie la validité des vecteurs découlant de la division de la région
 * @param tab un vecteur correspondant a une région d'une grille de sudoku
 * @return res un booléen, true si la region est valide, false sinon
 */

bool VerifDivisRegion(vector<int> tab){
    bool res = true;
    vector<int> countNum ={0,0,0,0,0,0,0,0,0};
    for(size_t i =0;i<tab.size();i++){
        if(tab.at(i) !=0){
            countNum.at(tab.at(i)-1) ++;
            if(countNum.at(tab.at(i)-1)>1){
                res = false;
            }
        }
    }
return res;
}

/** cette fonction sert a vérifier si la grille est valide
 * @param g une structure Grille, pas le vecteur grille associé à la structure
 * @return res un booléen, true si la grille est valide false sinon
 */

bool valide(const Grille &g) {
    //on commence par le plus simple, les lignes
    bool res = true;
    //parcourt une ligne correspondante à un vecteur et regarde si un numéro n'apparait pas deux fois
    for(size_t tg =0; tg<g.grille.size();tg++){
        vector<int> countNum ={0,0,0,0,0,0,0,0,0}; //on définit un vecteur qui permettra de compter l'apparition de chaque valeur
        for(size_t tl =0; tl<g.grille.at(tg).size();tl++){ //on regarde à tg à tl

            if(comprisEntre1et9(g.grille.at(tg).at(tl))){ //si le nombre est entre 1 et 9
                countNum.at(g.grille.at(tg).at(tl)-1) ++; // on le prend en compte dans notre tableau
                if(countNum.at(g.grille.at(tg).at(tl)-1)>1){ //on regarde si le nombre qu'on vient d'ajouter était déjà présent au moins une fois
                    res = false; //le cas échéant, on dit que c'est une grille non valide.
                }
            }
        }
    }
    //fin du test des lignes

    for(size_t tl = 0;tl<g.grille.at(0).size();tl++){ //on peut prendre un indice 0 car on sait que la grille est valide (toutes les tailles de lignes sont les mêmes)
        vector<int> countNum ={0,0,0,0,0,0,0,0,0}; //on définit un vecteur qui permettra de compter l'apparition de chaque valeur
        for(size_t tg = 0;tg<g.grille.size();tg++){ //on regarde à tg à tl

            if (comprisEntre1et9(g.grille.at(tg).at(tl))){ //si le nombre est entre 1 et 9
                countNum.at(g.grille.at(tg).at(tl)-1) ++; // on le prend en compte dans notre tableau
                if(countNum.at(g.grille.at(tg).at(tl)-1)>1){ //on regarde si le nombre qu'on vient d'ajouter était déjà présent au moins une fois
                    res = false; //le cas échéant, on dit que c'est une grille non valide.
                }
            }
        }
    }
    //fin du test des colonnes


    vector<int> V1 = DivisRegion(0,0,g.grille);
    vector<int> V2 = DivisRegion(3,0,g.grille);
    vector<int> V3 = DivisRegion(6,0,g.grille);
    vector<int> V4 = DivisRegion(0,3,g.grille);
    vector<int> V5 = DivisRegion(3,3,g.grille);
    vector<int> V6 = DivisRegion(6,3,g.grille);
    vector<int> V7 = DivisRegion(0,6,g.grille);
    vector<int> V8 = DivisRegion(3,6,g.grille);
    vector<int> V9 = DivisRegion(6,6,g.grille);
    /**
    |   1   |   4   |   7   |
    |   2   |   5   |   8   |
    |   3   |   6   |   9   |
    */



    if (!(VerifDivisRegion(V1) && VerifDivisRegion(V2) && VerifDivisRegion(V3) && VerifDivisRegion(V4) && VerifDivisRegion(V5) && VerifDivisRegion(V6) && VerifDivisRegion(V7) && VerifDivisRegion(V8) && VerifDivisRegion(V9))){
        res = false;
    }
    //fin de la vérification des régions

    return res;
}


/** fonction qui renvoie le vecteur des valeurs disponibles pour le couple d'indices ind compte-tenu des valeurs placées sur sa ligne, colonne et sa région
 * @param g une structure avec un nom et un vecteur de vecteur correspondant a la grille
 * @param ind une structure correspondant a un curseur pour parcourir la grille
 * @return res le vecteur des valeurs disponibles
 */

vector<int> possibles(const Grille &g, Indices ind) {
    if(g.grille.at(ind.lig).at(ind.col) !=0){
        return {};
    }
  vector<int> res (0);
  Grille GrilleF = g;
  for(int i =0; i <9;i++){
    GrilleF.grille.at(ind.lig).at(ind.col)= i+1;
        if (valide(GrilleF)){
            res.push_back(i+1);
        }
  }
  return res;
}


/** cette fonction est utile et permet de détecter la région dans laquel on se trouve en fonction des indices des lignes et des colonnes comme pour la division au dessus
 * @param i un entier pour parcourir les lignes
 * @param j un entier pour parcourir les colonnes
 * @return res un entier correspondant au numéro de la region
 */

int detectRegion(int i, int j){
    int res = 0;
    if(i <3){
            if(j <3){
                res = 1;
            }else if(j<6 and j>2){
                res =4;
            }else{
                res = 7;
            }
    }else if(i<6 and i>2){
            if(j <3){
                res =2;
            }else if(j<6 and j>2){
                res = 5;
            }else{
                res =8;
            }
    }else{
            if(j <3){
                res =3;
            }else if(j<6 and j>2){
                res=6;
            }else{
                res=9;
            }
    }
return res;
}
/* recoit en argument le vecteur des valeurs possibles pour la case
 * d'indices ij. Parcourt les valeurs en cherchant si pour l'une d'entre
 * elles il existe un seul emplacement valide dans la région.
 * Dans ce cas, stocke la valeur dans la case et renvoie true.
 * Renvoie false si pour chaque valeur possible il existe au moins deux
 * cases où on pourrait potentiellement la ranger. Dans ce cas ne
 * modifie pas la grille.
 */
 /** Parcourt les valeurs en cherchant si pour l'une d'entre
  * elles il existe un seul emplacement valide dans la région
  * @param g une structure avec un nom et un vecteur de vecteur correpondant a une grille
  * @param ij une structure pour parcourir la grille
  * @param vpossibles un vecteur de valeur possible
  * @return un booleen, renvoi true si une valeur est unique et a bien ete remplacee, false sinon
  *
  */

bool force(Grille &g, Indices ij, vector<int> vpossibles) {
    Grille GrilleF = g;
    int Indi = ij.lig;
    int Indj = ij.col;
    vector<int> indicesIetJ (4);
    int region = detectRegion(Indi,Indj); //on récupère la région de l'indice qu'on considère
    if(vpossibles.size() == 1){
        g.grille.at(Indi).at(Indj) = vpossibles.at(0);
        return true;
    }
    for(size_t k =0; k<vpossibles.size();k++){//boucle for pour chaque valeur de vpossibles

        bool Unique = true;
        //Décomposition des zones régions en fonction de la région dans laquelle on est

        if (region ==1){
            indicesIetJ ={0,2,0,2};
        }else if(region ==2){
            indicesIetJ ={3,5,0,2};
        }else if(region ==3){
            indicesIetJ ={6,8,0,2};
        }else if(region ==4){
            indicesIetJ ={0,2,3,5};
        }else if(region ==5){
            indicesIetJ ={3,5,3,5};
        }else if(region ==6){
            indicesIetJ ={6,8,3,5};
        }else if(region ==7){
            indicesIetJ ={0,2,6,8};
        }else if(region ==8){
            indicesIetJ ={3,5,6,8};
        }else{
            indicesIetJ ={6,8,6,8};
        }
        //on cherche ensuite les zones vide différentes des coordonnées que l'on a pour les remplacer et appliquer la fonction "valide"
        //si valide renvoie true, cela veut dire qu'il y a une autre position dans la région où le nombre peut aller
            for(int i =indicesIetJ.at(0);i<=indicesIetJ.at(1);i++){
                for(int j = indicesIetJ.at(2);j<=indicesIetJ.at(3);j++){
                    if(!(i == Indi && j== Indj)){
                        if(GrilleF.grille.at(i).at(j) ==0){     //on regarde si la case qu'on regarde est vide
                            GrilleF.grille.at(i).at(j) = vpossibles.at(k);  //on remplace par la première valeur possible de vpossibles
                            if(valide(GrilleF)){ //on regarde si cette case est correcte également
                                Unique = false;                     //dans ce cas la position de base n'était pas unique
                            }
                            GrilleF.grille.at(i).at(j) = 0;         //on remet la grille comme avant pour les prochains tests
                        }
                    }
                }
            }//fin des tests de la région
            if(Unique){         //si la case était unique
               // cout << "on a changé la case "<< Indi << ";" << Indj << " de la region "<< region<< " en "<<vpossibles.at(k)<< endl;
                g.grille.at(Indi).at(Indj) = vpossibles.at(k);  //on change la grille
                return true;                                    //et l'on return true, aucune des autres valeurs de la liste ne peuvent aller à cet endroit
            }
    }//fin de la boucle for de la taille de vpossibles
     //on a passé tout le vecteur des possibilités sans qu'aucune valeur ne soit unique, alors on return false
  return false;
}

/** cette fonction demande à l'utilisateur d'entrer une valeur pour un indice vide
 * @param g une structure avec un nom et un vecteur de vecteur correspondant a une grille de sudoku
 * @return res un booleen, renvoie true si la valeur entrée par l'utitilisateur a ete correctement remplacée, renvoi false sinon
 */

bool userSuggest(Grille &g) {
  cout << "Voici la grille a ce stade dans la résolution : "<< endl;
  imprime(g);
  bool res = false;
  int val;
  Indices Ind;
  //On entre les valeurs de l'utilisateur
  do{
      cout << "Veillez entrez l'indice (=0) de la valeur ou '10' pour annuler : "<< endl;

      cout << "Ligne : ";
      cin >> Ind.lig;
      cout << endl;
      cout << "Colonne : ";
      cin >> Ind.col;
      cout << endl;
      if(Ind.col == 10 || Ind.lig == 10){
        cout <<"Sortie de la suggestion"<< endl;
        return res;
      }
  }while(g.grille.at(Ind.lig).at(Ind.col)!=0); //on le refait tant que sa valeur n'est pas un 0
  cout << "Liste des valeurs possibles (Prendre uniquement parmi ces valeurs): ";
  vector<int> V = possibles(g,{Ind.lig,Ind.col});
    for(size_t i =0; i<V.size();i++){
        cout <<V.at(i)<< ",";
    }

  cout <<"Veuillez entrez une valeur a suggerer : "<< endl;
  cin >> val;
  bool estPossible = false;
  //On regarde si la cases est bien vide (encore un fois)
  if(g.grille.at(Ind.lig).at(Ind.col) == 0){
    vector<int> vpossibles = possibles(g,Ind); //on récupère la liste des valeurs possibles pour cette case
    for(size_t i =0; i<vpossibles.size();i++){
        //puis on regarde si la valeur de l'utilisateur est en accord avec cette liste (encore une fois)
        if(val == vpossibles.at(i)){
            estPossible = true;
        }
    }
    if(estPossible){    //si la valeur est possible alors on la remplace et on met res a true
        g.grille.at(Ind.lig).at(Ind.col) = val;
        res = true;
    }
  }
  //dans tout les autres cas ou à l'indice la valeur est différente de 0 ou que la valeur n'est pas possible, on retournera false
  return res;
}

/** cette fonction permet de vérifier si la grille a été remplie
 * @param g une structure avec un nom et un vecteur de vecteur correspondant a une grille de sudoku
 * @return res un booleen, renvoie true si la grille est pleine, renvoie false sinon
 */

bool estPleine(const Grille &g){
    bool res = true;
    for(size_t i =0; i<g.grille.size();i++){
        for(size_t j =0; j<g.grille.at(i).size();j++){
            if(g.grille.at(i).at(j)==0){
                res = false;
            }
        }
    }
    return res;
}

/** cette fonction compare deux grilles entre elles | On considère qu'elles sont de même taille
 * @param g1 une structure avec un nom et un vecteur de vecteur correspondant a une grille de sudoku
 * @param g2 une structure avec un nom et un vecteur de vecteur correspondant a la grille de sudoku une fois modifiée
 * @return res un booleen, renvoie true si les grilles sont identiques, renvoie false sinon
 */

bool comparaisonDeuxGrilles(Grille g1, Grille g2){
    bool res = true;
    for(size_t i =0; i<g1.grille.size();i++){
        for(size_t j = 0; j<g1.grille.at(i).size();j++){
            if(g1.grille.at(i).at(j) != g2.grille.at(i).at(j)){
                res = false;
            }
        }
    }
    return res;
}


/**  verifie si la grille est toujours valide (aucun indice n'a de vecteur possibilité de taille nulle)
 * @param g une structure avec un nom et un vecteur de vecteur correspondant a une grille de sudoku
 * @return res un booleen, renvoie true si la grille est toujours complétable, renvoi false sinon
 */

bool toujoursComp(const Grille g){
    bool res = true;
    for(size_t i = 0; i<g.grille.size();i++){
        for(size_t j = 0; j<g.grille.at(i).size();j++){
            if(g.grille.at(i).at(j) == 0){
                if(possibles(g,{i,j}).size() == 0){
                    res = false;
                }
            }
        }
    }
    return res;
}

/** fonction qui écrit dans la sauvegarde la grille avec les choix
 * @param g une structure avec un nom et un vecteur de vecteur correspondant a une grille de sudoku
 * @param i un entier désignant la ligne que l'on inscrit
 */
void EcritureLigneSave(Grille g,int i){
    ofstream monflux("sauvegarde.txt",ios::app);
    for(size_t k = 0; k < g.grille.at(i).size();k++){
        monflux << g.grille.at(i).at(k);
    }
}

/** fonction qui crée une nouvelle grille à partir d'une sauvegarde
 * @param save un tableau de string correspondant aux lignes de la sauvegarde
 * @param ligne un entier désignant la première ligne de la grille dans le tableau de sauvegarde
 * @return newGrille la grille que l'on viens de créer
 */
Grille CreationGrilleSave(vector<string> save, int ligne){

    Grille newGrille = { "GV",
		{ { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0}
		}
    };

    for(size_t i = 0 ; i<newGrille.grille.size();i++){
        for(size_t j =0; j< newGrille.grille.at(i).size();j++){
            char a = save.at(ligne).at(j);
            int ia = a - '0';
            newGrille.grille.at(i).at(j) = ia;
        }
    ligne ++;
    }
    cout <<"Grille faite à partir de la sauvegarde la plus récente : "<< endl;
    imprime(newGrille);
    return newGrille;
}



/** fonction qui resout le sudoku a l'aide des fonction precedente
 * @param g une structure avec un nom et un vecteur de vecteur correspondant a une grille de sudoku
 * @return res un booleen, renvoie true si la grille est résolue
 */

bool joue(Grille &g) {
    bool res = false;
    bool VaSave = false;
    bool VaRestaur = false;
    cout << endl << endl<< "Debut du traitement de la grille " << g.nom << endl;

    if(bienFormee(g)==false){
        cout<< "Grille mal formée"<<endl;
        return false;
    }
    cout << "Grille bien formée"<<endl;

    if(valide(g)==false){
        cout <<"Grille invalide"<<endl;
        return false;
    }
    cout << "Grille valide"<<endl<< "Grille initiale :"<<endl;
    imprime(g);

    cout << "Voulez vous sauvegarder les choix de cette partie ?"<<endl << " 'O' pour oui et 'N' pour non "<<endl;
    char ctmp;
    cin >> ctmp;
    if (ctmp == 'O'){
        VaSave = true;
    }
    cout << "Voulez vous charger les choix de la grille " << g.nom <<" ?"<<endl << " 'O' pour oui et 'N' pour non "<<endl;
    cin >> ctmp;

    if (ctmp=='O'){
        VaRestaur = true;
    }

    if (VaRestaur){
        ifstream monflux("sauvegarde.txt",ios::app);
        string ligne;
        vector<string> saves;
        while(getline(monflux, ligne)){ //Tant qu'on n'est pas à la fin, on lit
            saves.push_back(ligne);
        }
        bool remplaceFait = false;
        for(int act = saves.size()-1; act>=0 ; act--){
            if(saves.at(act) == g.nom and remplaceFait!= true){
                Grille NG = CreationGrilleSave(saves, act+1);
                for(size_t i =0; i<g.grille.size();i++){
                    for(size_t j = 0; j<g.grille.at(i).size();j++){
                        if(g.grille.at(i).at(j) == 0){
                            g.grille.at(i).at(j) = NG.grille.at(i).at(j);
                        }
                    }

                }
                remplaceFait = true;
                cout << "Chargement de la sauvegarde effectué"<< endl;
            }
        }
        cout << "On commence la résolution "<< endl;
    }

    while(!(estPleine(g))){
        Grille tmpGrille1 = g;
        for(size_t i =0; i<g.grille.size();i++){
            for(size_t j =0; j<g.grille.at(i).size();j++){
                if(g.grille.at(i).at(j)==0){
                    Indices Ind ={i,j};
                    force(g,Ind,possibles(g,Ind));
                }
            }
        }
        if(comparaisonDeuxGrilles(tmpGrille1,g)){ // si la grille n'a pas changé alors qu'on a fait un tour complet
            if(userSuggest(g)){
                cout <<"Remplacement effectué"<< endl;
                if(toujoursComp(g)== false){
                    cout <<"La grille n'est pas résoluble d'après la suggestion de l'utilisateur"<< endl;
                    cout <<"Fin de la résolution"<< endl;
                    cout << endl<<endl;
                    cout << "Voulez vous retournez à l'étape précédente ? "<<endl;
                    char c;
                    do{
                    cout << "O = oui, N = non"<<endl;
                    cin >> c;
                    }while(c!='O' && c!= 'N');
                    if(c == 'O'){
                        g = tmpGrille1;
                    }
                    else{
                        return false;
                    }
                }
                if (VaSave){
                    ofstream monflux("sauvegarde.txt",ios::app);
                    monflux <<endl<< g.nom << endl;
                    for(int b = 0; b<9;b++){
                        EcritureLigneSave(g,b);
                        monflux<<endl;
                    }
                }



            }
            else{
                cout <<"Erreur lors du remplacement"<< endl;
            }
        }
    }



    cout<< "Grille completée :"<<endl;
    imprime(g);
    return res;
}

/* quelques grilles prédéfinies */
int main() {
  // Les grilles G2 et G3 peuvent se résoudre sans aide de l'utilisateur
  Grille g2 = { "G2",
		{ { 5, 3, 0, 0, 7, 0, 0, 0, 0 },
		  { 6, 0, 0, 1, 9, 5, 0, 0, 0 },
		  { 0, 9, 8, 0, 0, 0, 0, 6, 0 },
		  { 8, 0, 0, 0, 6, 0, 0, 0, 3 },
		  { 4, 0, 0, 8, 0, 3, 0, 0, 1 },
		  { 7, 0, 0, 0, 2, 0, 0, 0, 6 },
		  { 0, 6, 0, 0, 0, 0, 2, 8, 0 },
		  { 0, 0, 0, 4, 1, 9, 0, 0, 5 },
		  { 0, 0, 0, 0, 8, 0, 0, 7, 9 }
		}};

  Grille g3 = { "G3",
		{ { 0, 2, 7, 0, 6, 5, 0, 4, 9 },
		  { 3, 5, 0, 0, 0, 9, 0, 0, 8 },
		  { 8, 9, 0, 0, 0, 0, 0, 0, 0 },
		  { 2, 0, 0, 0, 9, 0, 0, 0, 0 },
		  { 0, 0, 0, 6, 8, 7, 0, 0, 0 },
		  { 0, 0, 0, 0, 3, 0, 0, 0, 5 },
		  { 0, 0, 0, 0, 0, 0, 0, 6, 3 },
		  { 7, 0, 0, 2, 0, 0, 0, 8, 4 },
		  { 4, 8, 0, 9, 7, 0, 1, 5, 0}
		}};
  Grille g4 = { "G4",
		{ { 8, 0, 0, 0, 0, 0, 1, 0, 0 },
		  { 0, 3, 4, 0, 2, 0, 6, 0, 0 },
		  { 0, 9, 0, 4, 0, 0, 0, 0, 2 },
		  { 5, 1, 0, 0, 4, 2, 9, 6, 0 },
		  { 0, 0, 0, 0, 6, 0, 0, 0, 0 },
		  { 0, 6, 7, 1, 5, 0, 0, 2, 3 },
		  { 9, 0, 0, 0, 0, 4, 0, 3, 0 },
		  { 0, 0, 2, 0, 1, 0, 7, 4, 0 },
		  { 0, 0, 8, 0, 0, 0, 0, 0, 1 }
		}};
  // cette grille admet deux solutions différentes mais demande une aide
  // de l'utilisateur si on se limite aux deux autres stratégies définies
  Grille g5 = { "G5",
		{ { 0, 0, 8, 0, 0, 0, 2, 0, 0 },
		  { 0, 0, 4, 3, 0, 0, 0, 0, 1 },
		  { 0, 5, 0, 0, 0, 7, 0, 8, 9 },
		  { 0, 0, 5, 7, 4, 0, 0, 0, 2 },
		  { 0, 0, 0, 1, 0, 3, 0, 0, 0 },
		  { 4, 0, 0, 0, 2, 0, 6, 0, 0 },
		  { 2, 6, 0, 5, 0, 0, 0, 7, 0 },
		  { 5, 0, 0, 0, 0, 2, 9, 0, 0 },
		  { 0, 0, 1, 0, 0, 0, 5, 0, 0 }
		}};
		//SOLUTION SI ON SUGGERE UN 8 EN BAS A GAUCHE PUIS UN 3 A SA DROITE
		//On a aussi une solution pour un 7 en bas

  Grille gv = { "GV",
		{ { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0}
		}};

  Grille gmf = { "GMF",
		{ { 0, 0, 0, 0, 0, 0, 0, 0},
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		  { 0, 0, 0, 0, 0, 0, 0, 0, 0}
		}};

    Grille ginv = { "GINV",
		{ { 0, 0, 8, 0, 0, 0, 2, 0, 0 },
		  { 8, 0, 4, 3, 0, 0, 0, 0, 1 },
		  { 0, 5, 0, 0, 0, 7, 0, 8, 9 },
		  { 0, 0, 5, 7, 4, 0, 0, 0, 2 },
		  { 0, 0, 0, 1, 0, 3, 0, 0, 0 },
		  { 4, 0, 0, 0, 2, 0, 6, 0, 0 },
		  { 2, 6, 0, 5, 0, 0, 0, 7, 0 },
		  { 5, 0, 0, 0, 0, 2, 9, 0, 0 },
		  { 0, 0, 1, 0, 0, 0, 5, 0, 0 }
		}};


  joue(gmf);
  joue(ginv);

  joue(g3);
  joue(g4);

  joue(g5);
  g5 = { "G5",
		{ { 0, 0, 8, 0, 0, 0, 2, 0, 0 },
		  { 0, 0, 4, 3, 0, 0, 0, 0, 1 },
		  { 0, 5, 0, 0, 0, 7, 0, 8, 9 },
		  { 0, 0, 5, 7, 4, 0, 0, 0, 2 },
		  { 0, 0, 0, 1, 0, 3, 0, 0, 0 },
		  { 4, 0, 0, 0, 2, 0, 6, 0, 0 },
		  { 2, 6, 0, 5, 0, 0, 0, 7, 0 },
		  { 5, 0, 0, 0, 0, 2, 9, 0, 0 },
		  { 0, 0, 1, 0, 0, 0, 5, 0, 0 }
		}};
  joue(g5);
  g5 = { "G5",
		{ { 0, 0, 8, 0, 0, 0, 2, 0, 0 },
		  { 0, 0, 4, 3, 0, 0, 0, 0, 1 },
		  { 0, 5, 0, 0, 0, 7, 0, 8, 9 },
		  { 0, 0, 5, 7, 4, 0, 0, 0, 2 },
		  { 0, 0, 0, 1, 0, 3, 0, 0, 0 },
		  { 4, 0, 0, 0, 2, 0, 6, 0, 0 },
		  { 2, 6, 0, 5, 0, 0, 0, 7, 0 },
		  { 5, 0, 0, 0, 0, 2, 9, 0, 0 },
		  { 0, 0, 1, 0, 0, 0, 5, 0, 0 }
		}};
  joue(g5);




  return 0;
}

		// Fonctions fournies, rien à modifier a priori.


/* Imprime une ligne de séparation formée du caractère passé en argument */
void imprimeL(char c) {
  cout << ' ';
  for(size_t i = 0; i < 9; i += 1) { cout << c << c << c << c; }
  /* pour prendre en compte les espaces ajoutés près des '+' */
  cout << c << c << c << c << c << c;
  cout << endl;
}

/* suppose la grille bien formee: 9 lignes de 9 colonnes de chiffres de 0 à 9 */
void imprime(const Grille &g) {
  for(size_t i = 0; i < 9; i += 1) {
    imprimeL(i % 3 == 0 ? '+' : '-'); // ligne d'en-tete
    for(size_t j = 0; j < 9; j += 1) {
      char c = '0' + g.grille.at(i).at(j);
      cout << (j % 3 == 0 ? " + " : " " ) << ' ' << c << ' ';
    }
    cout << "+" << endl;
  }
  imprimeL('+'); // ligne finale du bas
  cout << endl;
}
