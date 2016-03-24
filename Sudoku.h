struct Backtrack{
  int value;
  int x;
  int y;
};
class Sudoku{
public:
  Sudoku();
  ~Sudoku();
  void readIn();
  void print();
  bool exam();
  bool row_exam();
  bool col_exam();
  bool cell_exam();
  void solve();
  int count_zero();
  void find_value( int value ,int& posX, int& posY );
  void wash( Backtrack *Node, int counter );
  int assign_value( Backtrack *Node, int posX, int posY, int current_state );
  bool Safe( int posX, int posY, int value );
  bool row_safe( int posX, int value );
  bool col_safe( int posY, int value );
  bool cell_safe( int posX, int posY, int value );
  void changeNum( int number_a, int number_b );
  void changeRow( int a, int b );
  void changeCol( int a, int b );
  void swap( int* element_1, int* element_2 );
  void flip( bool number );
  void rotate( int number );
  void transform();
  void reset_current_state( int& current_state );
  void solve_sub( int multiple , Backtrack* Node, int posX, int posY, int current_state, int counter );
  void reset_the_sudoku( Backtrack* Node, int counter );
  void find_value_reverse( int value , int& posX, int& posY );
  void copyFunc( int row, int col );
  bool isTheSame( int row, int col );
  void giveQuestion();
private:
  int** matrix;
  int** copy;
  int row;
  int col;
};
