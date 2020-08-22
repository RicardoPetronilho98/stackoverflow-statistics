package main.java.li3;

import java.util.ArrayList;
import java.time.LocalDate;
import java.lang.String;

import main.java.common.*;


public class TesteDados {
    public static void main(String[] args){

        try {


            Dados db = new Dados();

            ArrayList<Long> postsIds1 = new ArrayList<>();
            ArrayList<Long> postsIds2 = new ArrayList<>();
            ArrayList<Long> postsIds3 = new ArrayList<>();
            ArrayList<Long> postsIds4 = new ArrayList<>();
            ArrayList<Long> postsIds5 = new ArrayList<>();

            postsIds1.add(1l);
            postsIds2.add(2l);
            postsIds2.add(3l);
            postsIds2.add(4l);

            User u1 = new User(1, 22, "José", "Sou programador!", postsIds1, 2, 4, 1);
            User u2 = new User(2, 22, "André", "Sou programador!", postsIds2, 2, 4, 0);
            User u3 = new User(3, 22, "Ricardo", "Sou programador!", postsIds3, 2, 4, 0);
            User u4 = new User(4, 22, "Henrique", "Sou programador!", postsIds4, 2, 4, 1);
            User u5 = new User(5, 22, "Joana", "Sou programador!", postsIds5, 2, 4, 0);

            Post p1 = new Post(1, 1, 1, 0, "haskell", "HASKELL", LocalDate.now(), 2, 10, 3, 5, 1);
            Post p2 = new Post(2, 2, 2, 1, "haskell", "HASKELL", LocalDate.now(), 2, 10, 3, 5, 1);
            Post p3 = new Post(3, 2, 3, 1, "haskell", "HASKELL", LocalDate.now(), 2, 10, 3, 5, 1);
            Post p4 = new Post(4, 1, 4, 0, "haskell", "HASKELL", LocalDate.now(), 2, 10, 3, 5, 1);
            Post p5 = new Post(5, 2, 5, 4, "haskell", "HASKELL", LocalDate.now(), 2, 10, 3, 5, 1);


            db.add(u1);


            db.add(u2);


            db.add(u3);


            db.add(u4);


            db.add(u5);


            db.add(p1);


            db.add(p2);


            db.add(p3);


            db.add(p4);


            db.add(p5);


            System.out.println(db.toString());

            System.out.println(db.getUser(1l));
        } catch (ValoresInvalidosException e){
            e.printStackTrace();
        } catch (UserNaoExisteException e){
            e.printStackTrace();
        } catch (UserExisteException e){
            e.printStackTrace();
        } catch (PostExisteException e){
            e.printStackTrace();
        }

    }
}
