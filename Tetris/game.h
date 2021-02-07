#ifndef GAME_H
#define GAME_H



int calculScore(int score, int niveau, int nbLignes){
  int ajout;
  switch(nbLignes)
  {
    case 1:
      ajout=40;
      break;
    case 2:
      ajout=100;
      break;
    case 3:
      ajout=300;
      break;
    case 4:
      ajout=1200;
      break;
    default:
      std::cerr<<"Wrong number of lines destructed"<<std::enl;
      ajout=0;
      break;
  }
  return score+(niveau+1)*ajout;
}




#endif // !GAME_H
