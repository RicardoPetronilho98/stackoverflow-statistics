package main.java.engine;

import main.java.common.Post;

import java.util.Comparator;

public class ComparatorPostData implements Comparator<Post> {

    public int compare(Post p1, Post p2){

        if (p1.getData().isEqual(p2.getData())) return 0;
        else if (p1.getData().isBefore(p2.getData())) return -1;
        else return 1;
    }
}
