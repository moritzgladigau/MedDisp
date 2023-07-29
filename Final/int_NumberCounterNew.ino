//Value on display numbers 0-9 Count
  int NumberCounterNew(byte Up, byte Down, int Max, int Min, int Start){
    if(Up == 1 && Start <= Max){
      return Start+1;
    }
    if(Down == 1 && Start >= Min){
      return Start-1;
    }
    return Start;
  }