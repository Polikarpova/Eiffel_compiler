/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Rtl;

/**
 *
 * @author Пользователь
 */
public class Io {
    
    void put_string( String v ) {
    
        System.out.print(v);
    }
    
    void put_integer( int v) {
        System.out.print(v);
    }
    
    void put_real( double v) {
    
        System.out.print(v);
    }
    
    void put_boolean( boolean v) {
    
        System.out.print(v ? "True" : "False");
    }
    
    void new_line() {
    
        System.out.println();
    }
}
