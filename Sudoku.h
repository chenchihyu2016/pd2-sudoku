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
  void solve();
  void changeNum( int number_a, int number_b );
  void changeRow( int a, int b );
  void changeCol( int a, int b );
  void flip( bool number );
  void rotate( int number );
  void transform();
  void giveQuestion();
private:
  int** matrix;
  int** copy;
  void print();
  bool exam();
  bool row_exam();
  bool col_exam();
  bool cell_exam();
  int count_zero();
  void find_zero( int& posX, int& posY );
  void wash( Backtrack *Node, int counter, int number );
  int assign_value( bool mutiple, Backtrack *Node, int posX, int posY, int current_state );
  bool Safe( int posX, int posY, int value );
  bool row_safe( int posX, int value );
  bool col_safe( int posY, int value );
  bool cell_safe( int posX, int posY, int value );
  void swap( int* element_1, int* element_2 );
  void reset_current_state( int& current_state );
  bool solve_sub( bool multiple, Backtrack* Node, int posX, int posY, int current_state, int counter );
  void reset_the_sudoku( Backtrack* Node, int counter );
  void copyFunc();
  bool NotTheSame();
};
