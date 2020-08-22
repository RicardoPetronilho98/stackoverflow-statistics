package main.java.engine;

import main.java.common.Dados;
import main.java.common.User;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class Q2 {
    /**
     * Função que obtém o top N utilizadores com maior número de posts(perguntas e respostas)
     * @param N número de utilizadores
     * @param dados dados
     * @return retorna os N utilizadores com maior número de posts (perguntas e respostas)
     */
    public static List<Long> topMostActive(int N, Dados dados){
        ArrayList<Long> usersIds = new ArrayList<Long>(N);
        ArrayList<User> users = new ArrayList<User>();
        int i = 0;

        for(User user : dados.getUsers().values())
            users.add(user);

        users.sort(new ComparatorUserNumeroPosts());

        for(i = 0; i < N; i++){
            User user = users.get(i);
            usersIds.add(user.getId());
        }

        return usersIds;
    }
}
