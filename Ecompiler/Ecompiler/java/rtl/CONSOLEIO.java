package rtl;

import java.util.Scanner;
/**
 *
 * @author Пользователь
 */
public class CONSOLEIO {

    String last_string;
    int last_integer;
    float last_real;
    boolean last_boolean;
    char last_character;
    Scanner in;
    
    public CONSOLEIO() {
        this.in = new Scanner(System.in);
    }
        //data from stdin
    public void read_line() {
        this.last_string = in.nextLine();
    }
    public void read_integer() {
        this.last_integer = in.nextInt();
    }
    public void read_real() {
        this.last_real= in.nextFloat();
    }
    public void read_boolean() {
        this.last_boolean = in.nextBoolean();
    }
    public void read_character() {
        this.last_character = (char)in.nextInt();
    }
    
	// writing to stdout
    public void put_string( String v ) {
        System.out.print(v);
    }
    public void put_integer( int v) {
        System.out.print(v);
    }
    public void put_real( float v) {
        System.out.print(v);
    }
    public void put_boolean( boolean v) {
        System.out.print(v ? "True" : "False");
    }
    public void put_character( char v) {
        System.out.print((char)v);
    }
    public void new_line() {
        System.out.println();
    }
}
