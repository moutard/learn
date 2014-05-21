  cout << intersectBlock(s, Block(Vecteur(3,2), Vecteur(4,2))) << " " << "1" << endl;
  cout << intersectBlock(s, Block(Vecteur(4,2), Vecteur(6,4))) << " " << "1" << endl;
  cout << intersectBlock(s, Block(Vecteur(1,0), Vecteur(3,1))) << " " << "1" << endl;
  cout << intersectBlock(s, Block(Vecteur(1,1), Vecteur(3,2))) << " " << "1" << endl;
  cout << intersectBlock(s, Block(Vecteur(0,2), Vecteur(1,4))) << " " << "0" << endl;
  cout << intersectBlock(s, Block(Vecteur(0,1), Vecteur(1,2))) << " " << "0" << endl;
  cout << intersectBlock(s, Block(Vecteur(3,0), Vecteur(4,1))) << " " << "0" << endl;
  cout << intersectBlock(s, Block(Vecteur(4,0), Vecteur(6,1))) << " " << "0" << endl;
  cout << intersectBlock(s, Block(Vecteur(1,2), Vecteur(3,4))) << " " << "0" << endl;
  cout << intersectBlock(s, Block(Vecteur(3,1), Vecteur(4,2))) << " " << "0" << endl;
  cout << intersectBlock(s, Block(Vecteur(4,1), Vecteur(6,2))) << " " << "0" << endl;
  Segment s1(Vecteur(1, 0), Vecteur(0, 1));
  Segment s2(Vecteur(0, 0), Vecteur(1, 1));
  Vecteur v(5,5);

  intersectSegments(s1, s2, v);

  Segment s(Vecteur(0,0), Vecteur(6,4));
  intersectBlock(s, Block(Vecteur(4,1), Vecteur(6,2)));
