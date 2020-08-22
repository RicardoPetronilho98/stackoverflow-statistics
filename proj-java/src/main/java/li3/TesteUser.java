package main.java.li3;

import main.java.common.User;
import main.java.common.ValoresInvalidosException;

import java.util.ArrayList;

public class TesteUser {
    public static void main(String[] args){

        try {
            User u1 = new User(1, 22, "José", "Sou programador!", new ArrayList<Long>(), 2, 4, 0);
            User u2 = new User(u1);

            System.out.println(u1);
            System.out.println(u2);

            System.out.println(u1.equals(u2));

        } catch (ValoresInvalidosException e){
            e.printStackTrace();
        }
    }
}
