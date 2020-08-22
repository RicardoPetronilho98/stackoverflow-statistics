package main.java.li3;

import main.java.common.Tag;
import main.java.common.ValoresInvalidosException;

public class TesteTag {
    public static void main(String[] args){

        try {

            Tag t1 = new Tag(1, "HASKELL");
            Tag t2 = new Tag(2, "ANDROID");
            Tag t3 = new Tag(3, "Google");
            Tag t4 = new Tag(t3);

            System.out.println(t1.toString());
            System.out.println(t2.toString());
            System.out.println(t3.toString());

            System.out.println(t3.equals(t4));

        } catch (ValoresInvalidosException e){
            e.printStackTrace();
        }
    }
}
