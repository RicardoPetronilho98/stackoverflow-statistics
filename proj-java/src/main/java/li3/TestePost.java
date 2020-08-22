package main.java.li3;

import main.java.common.Post;
import main.java.common.ValoresInvalidosException;

import java.time.LocalDate;

public class TestePost {

    public static void main(String[] args){

        try {
            Post post1 = new Post();
            Post post2 = new Post(-1, 0, 1, 2, "titulo", "tags", LocalDate.now(), 3, 4, 5, 6, 7);
            Post post3 = new Post(-1, 0, 1, 2, "titulo", "tags", LocalDate.now(), 3, 4, 5, 6, 7);

            System.out.println(post1);
            System.out.println(post2);
            System.out.println(post1.equals(post2));
            System.out.println(post2.equals(post3));
        } catch (ValoresInvalidosException e){
            e.printStackTrace();
        }
    }
}
