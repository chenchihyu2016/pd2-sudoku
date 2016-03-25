/* Sudoku.cpp */
#include<iostream>
#include"Sudoku.h"
using namespace std;

Sudoku::Sudoku(){
	row = 9;
	col = 9;
	matrix = new int*[row];
	for( int i = 0; i < row; i++ ) matrix[i] = new int[col];
	for( int i = 0; i < row; i++ ){
		for(int j = 0; j < col; j++  )
			matrix[i][j] = 0;
	}
}
Sudoku::~Sudoku(){
	//for( int k = 0; k < row; k++ ) delete []matrix[k];
	//delete []Sudoku;
}
void Sudoku::readIn(){
	int k, counter = 0;
	while( ( counter < row*col ) && ( cin >> k ) ){
		matrix[ counter/row ][ counter%col ] = k;
		counter++;
	}
}
void Sudoku::print(){
	for( int i = 0; i < row ; i++ ){
		for( int j = 0; j < col; j++ ){
			cout << matrix[i][j] <<" ";
		}
		cout << endl;
	}
}
bool Sudoku::exam(){
	if ( row_exam() && col_exam() && cell_exam() )
		return true;
	else
		return false;
}
bool Sudoku::row_exam(){
	int* array_a = new int[col];
	bool control = true;

	for( int i = 0; i < row; i++ ){
		for( int l = 0; l < col; l++ )
			array_a[l] = 0;
		for( int j = 0; j < col; j++ )
			array_a[ matrix[i][j] - 1 ]++;
		for( int k = 0; k < col; k++ ){
			if( array_a[k] > 1 ){
				k = col;
				i = row;																																// To stop the loop
				control = false;
			}
		}
	}
	//delete []array_a;
	return control;
}
bool Sudoku::col_exam(){
	int* array_b = new int[row];
	bool control = true;

	for( int j = 0; j < col; j++ ){
		for( int i = 0; i < row; i++ )
			array_b[i] = 0;
		for( int i = 0; i < col; i++ )
			array_b[ matrix[i][j] - 1 ]++;
		for( int k = 0; k < row; k++ ){
			if( array_b[k] > 1 ){
				k = row;
				j = col;
				control = false;
			}
		}
	}
	//delete []array_b;
	return control;
}
bool Sudoku::cell_exam(){
	int* array_c = new int[col];
	bool control = true;

	for( int i = 0; i < row-2; i = i+3 ){							 														// Imporant parameters here
		for( int j = 0; j < col-2; j = j+3 ){						 														// 3 digits per cell
			for( int k = 0; k < col; k++ )
				array_c[k] = 0;
			for( int p = i; p < i+3; p++ ){
				for( int q = j; q < j+3; q++ ){
					array_c[ matrix[p][q] -1 ]++;
				}
			}
		}
		for( int k = 0; k < col; k++ ){
			if( array_c[k] > 1 ){
				k = col;
				i = row;
				control = false;
			}
		}
	}
	//delete []array_c;
	return control;
}
void Sudoku::solve(){
	if( exam() == 0 )
		cout << "0" << endl;
	else{
		int posX,posY;
		bool track = 1;
		int current_state = 0;
		int counter = count_zero();
		copy = new int*[row];
		for( int k = 0; k < row; k++ ) copy[k] = new int[col];

		Backtrack *Node = new Backtrack[counter];
		wash( Node, counter, 0 );
		find_value( 0, posX, posY );
		solve_sub( 1, Node, posX, posY, current_state, counter, track );
		copyFunc();
		reset_the_sudoku( Node, counter );
		if( track != 0 ){
			reset_current_state( current_state );
			wash( Node, counter, 1 );
			find_value( 0, posX, posY );
			solve_sub( 2 , Node, posX, posY, current_state, counter, track );
			if( !isTheSame() ){
				cout << '2' << endl;
			}
			else{
				cout << '1' << endl;
				for( int i = 0; i < row ; i++){
					for( int j = 0; j < col; j++ )
						cout << copy[i][j] << " " ;
					cout << endl;
				}
			}
		}
		else cout << '0' << endl ;
	}
}
int Sudoku::count_zero(){
	int counter = 0 ;
	for( int i = 0; i < row; i++ ){
		for( int j = 0; j < col; j++ ){
			if( matrix[i][j] == 0 )
				counter++;
		}
	}
	return counter;
}
void Sudoku::find_value( int value ,int& posX, int& posY ){
	for( int i = 0; i < row; i++ ){
		for( int j = 0; j < col; j++ ){
			if( matrix[i][j] == value ){
				posX = i;
				posY = j;
				j = col;
				i = row;
			}
		}
	}
}
void Sudoku::wash( Backtrack *Node, int counter, int number ){
	if( number == 0 ){
		for( int i = 0; i < counter; i++ )
			Node[i].value = 0;
	}
	else
		for( int i = 0; i < counter; i++ )
			Node[i].value = 9;
}
int Sudoku::assign_value( int multiple, Backtrack *Node, int posX, int posY, int current_state ){
	if( multiple == 1 ){
		Node[current_state].value++;
		while( !Safe( posX, posY, Node[current_state].value ) ){
			Node[current_state].value++;
		}
		return Node[current_state].value;
	}
	else if( multiple == 2 ){
		Node[current_state].value--;
		while( !Safe( posX, posY, Node[current_state].value ) ){
			Node[current_state].value--;
		}
		return Node[current_state].value;
	}
}
bool Sudoku::Safe( int posX, int posY, int value ){
	if( row_safe( posX, value ) && col_safe( posY, value ) && cell_safe( posX, posY, value ) )
	 	return true;
	else return false;
}
bool Sudoku::row_safe( int posX, int value ){
	bool control = 1;
	for( int j = 0; j < col; j++ ){
		if( value == matrix[posX][j] ){
			j = col;
			control = 0;
		}
	}
	return control;
}
bool Sudoku::col_safe( int posY, int value ){
	bool control = 1;
	for( int i= 0; i < row; i++ ){
		if( value == matrix[i][posY]){
			i = row;
			control = 0;
		}
	}
	return control;
}
bool Sudoku::cell_safe( int posX, int posY, int value ){
	bool control = 1;
	if( posX >= 6 ) posX = 6;
	else if ( posX >= 3 ) posX = 3;
	else posX = 0;
	if( posY >= 6 ) posY = 6;
	else if ( posY >= 3 ) posY = 3;
	else posY = 0;
		for( int r = posX; r <= posX+2; r++ ){
			for( int t = posY; t <= posY+2; t++ ){
				if( value == matrix[r][t]){
					control = 0;
					r = posX+3;
					t = posY+3;
				}
			}
	}
	return control;
}
void Sudoku::changeNum( int number_a, int number_b ){
	for( int i = 0; i < row; i++ ){
		for( int j = 0; j < col; j++ ){
			if( matrix[i][j] == number_a )
				matrix[i][j] = 0;
		}
	}
	for( int i = 0; i < row; i++ ){
		for( int j = 0; j < col; j++ ){
			if( matrix[i][j] == number_b )
				matrix[i][j] = number_a;
			else if ( matrix[i][j] == 0 )
				matrix[i][j] = number_b;
		}
	}

}
void Sudoku::changeRow( int a, int b ){
	if( a != 0 ) a = a*3;
	if( b != 0 ) b = b*3;
	if( a != b ){
		for( int i = 0 ; i < 3; i++ ){
			for( int j = 0 ; j < col; j++ ){
				swap( &matrix[a+i][j], &matrix[b+i][j]);
			}
		}
	}
}
void Sudoku::changeCol( int a, int b ){
	if( a != 0 ) a = a*3;
	if( b != 0 ) b = b*3;
	if( a != b ){
		for( int j = 0; j < 3; j++ ){
			for( int i = 0; i < row; i++ ){
				swap( &matrix[i][a+j], &matrix[i][b+j ]);
			}
		}
	}
}
void Sudoku::swap( int* element_1, int* element_2 ){
	int hold = *element_1;
	*element_1 = *element_2;
	*element_2 = hold;
}
void Sudoku::flip( bool number ){
	if( number == 0 ){																														//vertically
		for( int i = 0; i < 4; i++ ){
			for( int j = 0; j < col; j++ )
				swap( &matrix[i][j], &matrix[8-i][j]);
		}
	}
	else {																																				//horizontally
		for( int j = 0; j < 4; j++ ){
			for( int i = 0; i < row; i++ )
				swap( &matrix[i][j], &matrix[i][8-j]);
		}
	}
}
void Sudoku::rotate( int number ){
	number = number%4;
	if( number != 0 ){
		int **array = new int*[row];
		for( int i = 0; i < row; i++ )	array[i] = new int[col];
		for( int i = 0; i < row; i++ ){
			for( int j = 0; j < col; j++ )
				array[i][j] = matrix[i][j];
		}
		if( number == 1 ){
			for( int i = 0; i < row; i++ ){
				for( int j = 0; j < col; j++ )
					matrix[i][j] = array[8-j][i];
			}
		}
		else if( number == 2 ){
			for( int i = 0; i < row; i++){
				for( int j = 0; j < col; j++ )
					matrix[i][j] = array[8-i][8-j];
			}
		}
		else {
			for( int i = 0; i < row; i++ ){
				for( int j = 0; j < col; j++)
					matrix[i][j] = array[j][8-i];
			}
		}
		//for( int k = 0; k < col; k++ ) delete []array[k];
		//delete []array;
	}
}
void Sudoku::transform(){
	flip( 0 );
	rotate( 49 );
	changeCol( 2, 0 );
	print();
}
void Sudoku::reset_current_state( int& current_state ){
	current_state = 0;
}
void Sudoku::solve_sub( int multiple , Backtrack* Node, int posX, int posY, int current_state, int counter, bool& track  ){
	while( current_state < counter ){
	  int x = assign_value( multiple, Node, posX, posY, current_state );
		if ( x <= 9 ){
			Node[current_state].x = posX;
			Node[current_state].y = posY;
			Node[current_state].value = x;
			matrix[posX][posY] = x;
			current_state++;
			find_value( 0, posX, posY );
		}
		else {
			Node[current_state].value = 0;
			matrix[posX][posY] = 0;
			current_state--;
			posX = Node[current_state].x;
			posY = Node[current_state].y;
		}
		if( current_state < 0 ){
			current_state = counter;
			track = 0;
		}
	}
	//delete []Node;
}
void Sudoku::reset_the_sudoku( Backtrack* Node, int counter ){
	for( int k = 0; k < counter; k++ ){
		matrix[Node[k].x][Node[k].y] = 0;
	}
}
void Sudoku::copyFunc(){
	for( int i = 0; i < row; i++ ){
		for( int j = 0; j < col; j++ )
			copy[i][j] = matrix[i][j];
	}
}
bool Sudoku::isTheSame(){
	bool control = 0;
	for( int i = 0; i < row; i++){
		for( int j = 0; j < col; j++ ){
				if( copy[i][j] != matrix[i][j]){
					control = 1;
					i = row;
					j = col;
				}
		}
	}
	return control;
}
void Sudoku::giveQuestion(){
	matrix[0][1] = 8;
	matrix[0][4] = 1;
	matrix[0][7] = 2;
	matrix[1][0] = 6;
	matrix[1][3] = 3;
	matrix[1][5] = 5;
	matrix[1][8] = 1;
	matrix[2][2] = 7;
	matrix[2][6] = 4;
	matrix[3][1] = 2;
	matrix[3][3] = 1;
	matrix[3][5] = 9;
	matrix[3][7] = 5;
	matrix[4][0] = 7;
	matrix[4][8] = 6;
	matrix[5][1] = 9;
	matrix[5][3] = 6;
	matrix[5][5] = 3;
	matrix[5][7] = 4;
	matrix[6][2] = 5;
	matrix[6][6] = 3;
	matrix[7][0] = 9;
	matrix[7][3] = 2;
	matrix[7][5] = 1;
	matrix[7][8] = 8;
	matrix[8][1] = 3;
	matrix[8][4] = 6;
	matrix[8][7] = 7;
	print();
}
