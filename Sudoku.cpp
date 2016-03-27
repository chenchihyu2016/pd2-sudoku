/* Sudoku.cpp */
#include<iostream>
#include"Sudoku.h"
using namespace std;

Sudoku::Sudoku(){
	matrix = new int*[9];
	copy = new int*[9];
	for( int k = 0; k < 9; k++ ){
		matrix[k] = new int[9];
		copy[k] = new int[9];
	}
	for( int i = 0; i < 9; i++ ){
		for(int j = 0; j < 9; j++ ){
			matrix[i][j] = 0;
			copy[i][j] = 0;
		}
	}
}
Sudoku::~Sudoku(){
	for( int k = 0; k < 9; k++ ){
		delete []matrix[k];
		delete []copy[k];
	}
	delete []matrix;
	delete []copy;
}
void Sudoku::readIn(){
	int k, counter = 0;
	while( ( counter < 81 ) && ( cin >> k ) ){
		matrix[ counter / 9][ counter % 9 ] = k;
		counter++;
	}
}
void Sudoku::print(){
	for( int i = 0; i < 9; i++ ){
		for( int j = 0; j < 9; j++ ){
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
	int* array_a = new int[10];

	for( int i = 0; i < 9; i++ ){
		for( int l = 0; l < 10; l++ )
			array_a[l] = 0;
		for( int j = 0; j < 9; j++ ){
			if( matrix[i][j] == 0 ) continue;
			array_a[ matrix[i][j] ]++;
		}
		for( int k = 1; k < 10 ; k++ ){
			if( array_a[k] > 1 ){
				return false;
			}
		}
	}
	delete []array_a;
	return true;
}
bool Sudoku::col_exam(){
	int* array_b = new int[10];

	for( int j = 0; j < 9; j++ ){
		for( int k = 0; k < 10; k++ )
			array_b[k] = 0;
		for( int i = 0; i < 9; i++ ){
			if( matrix[i][j] == 0 ) continue;
				array_b[ matrix[i][j] ]++;
		}
		for( int k = 1; k < 10; k++ ){
			if( array_b[k] > 1 ){
				return false;
			}
		}
	}
	delete []array_b;
	return true;
}
bool Sudoku::cell_exam(){
	int* array_c = new int[10];

	for( int i = 0; i <= 6 ; i = i+3 ){							 														// Imporant parameters here
		for( int j = 0; j <= 6; j = j+3 ){						 														// 3 digits per cell
			for( int k = 0; k < 10; k++ )
				array_c[k] = 0;
			for( int p = i; p < i+3; p++ ){
				for( int q = j; q < j+3; q++ ){
					if ( matrix[p][q] == 0 ) continue;
					array_c[ matrix[p][q] ]++;
				}
			}
		}
		for( int k = 1; k < 10; k++ ){
			if( array_c[k] > 1 ){
				return false;
			}
		}
	}
	delete []array_c;
	return true;
}
void Sudoku::solve(){
	int counter = count_zero();
	if( exam() == 0 )
		cout << '0' << endl;
	else if ( counter > 65 )
		cout << '2' << endl;
	else{
		Backtrack *Stack = new Backtrack[counter];

		wash( Stack, counter, 0 );
		findAllZero( Stack );
		bool track = solve_sub( 0, Stack, counter );
		copyFunc();
		reset_the_sudoku( Stack, counter );
		if( track == false )
			cout << '0' << endl;
		else {
			wash( Stack, counter, 1 );
			solve_sub( 1, Stack, counter );
			if( NotTheSame() )
				cout << '2' << endl;
			else{
				cout << '1' << endl;
				for( int i = 0; i < 9 ; i++ ){
					for( int j = 0; j < 9; j++ )
						cout << copy[i][j] << " " ;
					cout << endl;
				}
			}
		}
	}
}
int Sudoku::count_zero(){
	int counter = 0 ;
	for( int i = 0; i < 9; i++ )
		for( int j = 0; j < 9; j++ )
			if( matrix[i][j] == 0 )
				counter++;
	return counter;
}
void Sudoku::findAllZero( Backtrack* Stack ){
	int current = 0;
	for( int i = 0; i < 9; i++ )
		for( int j = 0; j < 9; j++ )
			if( matrix[i][j] == 0 ){
				Stack[current].x = i;
				Stack[current].y = j;
				current++;
			}
}
void Sudoku::wash( Backtrack *Stack, int counter, int number ){
	int init_value = ( number == 0 ? 0 : 10 ) ;
	for( int i = 0; i < counter; i++ )
		Stack[i].value = init_value;
}
int Sudoku::assign_value( bool multiple, Backtrack *Stack, int current_state ){
		int delta = 1;
		if( multiple == 1 ) delta = -1;
		Stack[current_state].value += delta;
		while( !Safe( Stack[current_state].x, Stack[current_state].y, Stack[current_state].value ) )
			Stack[current_state].value += delta;
		return Stack[current_state].value;
}
bool Sudoku::Safe( int posX, int posY, int value ){
	if( row_safe( posX, value ) )
		if( col_safe( posY, value ) )
			if ( cell_safe( posX, posY, value ) )
	 			return true;
 return false;
}
bool Sudoku::row_safe( int posX, int value ){
	for( int j = 0; j < 9; j++ )
		if( value == matrix[posX][j] )
			return false;
	return true;
}
bool Sudoku::col_safe( int posY, int value ){
	for( int i= 0; i < 9; i++ )
		if( value == matrix[i][posY])
			return false;
	return true;
}
bool Sudoku::cell_safe( int posX, int posY, int value ){
	posX -= posX % 3;
	posY -= posY % 3;
	for( int r = posX; r <= posX+2; r++ )
		for( int t = posY; t <= posY+2; t++ )
			if( value == matrix[r][t])
					return false;
	return true;
}
void Sudoku::changeNum( int number_a, int number_b ){
	if ( number_a != number_b ){
		for( int i = 0; i < 9; i++ ){
			for( int j = 0; j < 9; j++ ){
				if( matrix[i][j] == number_a )
					matrix[i][j] = number_b;
				else if ( matrix[i][j] == number_b )
			  	matrix[i][j] = number_a;
				}
			}
	}
}
void Sudoku::changeRow( int a, int b ){
	if( a != 0 ) a = a*3;
	if( b != 0 ) b = b*3;
	if( a != b )
		for( int i = 0 ; i < 3; i++ )
			for( int j = 0 ; j < 9; j++ )
				swap( &matrix[a+i][j], &matrix[b+i][j]);
}
void Sudoku::changeCol( int a, int b ){
	if( a != 0 ) a = a*3;
	if( b != 0 ) b = b*3;
	if( a != b )
		for( int j = 0; j < 3; j++ )
			for( int i = 0; i < 9; i++ )
				swap( &matrix[i][a+j], &matrix[i][b+j]);
}
void Sudoku::swap( int* element_1, int* element_2 ){
	int hold = *element_1;
	*element_1 = *element_2;
	*element_2 = hold;
}
void Sudoku::flip( bool number ){
	if( number == 0 ){																														//vertically
		for( int i = 0; i < 4; i++ )
			for( int j = 0; j < 9; j++ )
				swap( &matrix[i][j], &matrix[8-i][j]);
	}
	else {																																				//horizontally
		for( int j = 0; j < 4; j++ )
			for( int i = 0; i < 9; i++ )
				swap( &matrix[i][j], &matrix[i][8-j]);
	}
}
void Sudoku::rotate( int number ){
	int **array = new int*[9];
	for( int i = 0; i < 9; i++ )	array[i] = new int[9];
	for( int i = 0; i < 9; i++ )
		for( int j = 0; j < 9; j++ )
			array[i][j] = matrix[i][j];
	if( number%4 == 1 )
		for( int i = 0; i < 9; i++ )
			for( int j = 0; j < 9; j++ )
				matrix[i][j] = array[8-j][i];
	else if( number%4 == 2 )
		for( int i = 0; i < 9; i++)
			for( int j = 0; j < 9; j++ )
				matrix[i][j] = array[8-i][8-j];
	else if( number%4 == 3 )
		for( int i = 0; i < 9; i++ )
			for( int j = 0; j < 9; j++)
				matrix[i][j] = array[j][8-i];
	for( int k = 0; k < 9; k++ ) delete []array[k];
	delete []array;
}
void Sudoku::transform(){
	flip( 0 );
	rotate( 49 );
	changeCol( 2, 0 );
	print();
}
bool Sudoku::solve_sub( bool multiple, Backtrack* Stack, int counter ){
	int current_state = 0;
	while( current_state < counter ){
	  int temp = assign_value( multiple, Stack, current_state );
		if ( temp <= 9 && temp >= 1 ){
			Stack[current_state].value = temp;
			matrix[Stack[current_state].x][Stack[current_state].y] = temp;
			current_state++;
		}
		else {
			int reset_value = ( multiple == 0 ? 0 : 10 );
			Stack[current_state].value = reset_value ;
			matrix[Stack[current_state].x][Stack[current_state].y] = reset_value;
			current_state--;
		}
		if( current_state < 0 )
			return false;
	}
	return true;
}
void Sudoku::reset_the_sudoku( Backtrack* Stack, int counter ){
	for( int k = 0; k < counter; k++ ){
		matrix[Stack[k].x][Stack[k].y] = 0;
	}
}
void Sudoku::copyFunc(){
	for( int i = 0; i < 9; i++ )
		for( int j = 0; j < 9; j++ )
			copy[i][j] = matrix[i][j];
}
bool Sudoku::NotTheSame(){
	for( int i = 0; i < 9; i++)
		for( int j = 0; j < 9; j++ )
			if( copy[i][j] != matrix[i][j] )
				return true;
	return false;
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
