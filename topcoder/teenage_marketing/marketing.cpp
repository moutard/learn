class Marketing
{
  public:
    bool adj[50][50];
    //0 no color
    //1 red
    //2 blue
    int color[50];
    int n;
    bool error;
  int64 howMany(vector <string> compete)
  {
    error = false;
    for(int i=0;i<50;i++)
      for(int j=0;j<50;j++)
      {
        adj[i][j] = false;
      }

    for(int i=0;i<compete.size();i++)
    {
      istringstream in(compete[i]);
      int n;
      while(in>>n)
      {
        adj[i][n] = adj[n][i] = true;
      }
      color[i] = 0;
    }
    int64 ways = 1;

    for(int i=0;i<compete.size();i++)
    {
      if(color[i] == 0)
      {
        colorit(i,1);
        if(error) return -1;
        ways *= 2;
      }
    }
    return ways;
  }
  void colorit(int i,int c)
  {
    if(color[i] != 0)
    {
      if(color[i] != c)
        error = true;
      return;
    }
    else
    {
      color[i] = c;
      int other=0;
      if(c == 1)
        other = 2;
      else
        other = 1;
      for(int j=0;j<50;j++)
      {
        if(adj[i][j])
        {
          colorit(j,other);
        }
      }
    }
  }
};
