package main.java.engine;

import main.java.common.*;

import java.time.LocalDate;
import java.util.*;
import java.util.stream.Collectors;

/**
 * Dado um intervalo arbitrário de tempo, devolver os
 * identificadores das N tags mais usadas pelos N utilizadores com melhor reputação.
 * Em ordem decrescente do número de vezes em que a tag foi usada.
 */


public class Q11 {
    /**
     *
     * @param dados base de dados com toda a informação do sistema
     * @param N  número de tag ids requeridos
     * @param begin data de inicio da procura
     * @param end data de fim da procura
     * @return retorna uma lisrta de tag ids
     * @throws TagNaoExisteException devolve excepção de tag não existente
     */
    public static List<Long> mostUsedBestRep(Dados dados, int N, LocalDate begin, LocalDate end) throws PostNaoExisteException,TagNaoExisteException{
        // N users com melhor reputação
        int size = 0;
        List<User> users = new ArrayList<>(dados.getUsersPorDataCollection(begin,end));
        users.sort(new ComparatorUserMaiorReputacao());
        List<User> biggestUsers = new ArrayList<>();
        while(size<N){
            biggestUsers.add(users.get(size));
            size++;
        }
        // lista com os posts Ids dos N users com mais reputação
        List <Long> postIds = biggestUsers.stream().map(User::getPostsIds).flatMap(Collection::stream).collect(Collectors.toList());
        List<String> multiTags = new ArrayList<>();
        for (Long id : postIds){
            Post p = dados.getPost(id);
            if(((p.getData().isAfter(begin) && p.getData().isBefore(end)) || p.getData().isEqual(begin) || p.getData().isEqual(end))){
                multiTags.add(p.getTags());
            }
        }
        List<Pair<String,Integer>> tags = multiTags.stream().map(p->p.split("[<>]")).flatMap(p->Arrays.stream(p)).sorted().map(p -> new Pair<>(p,1)).collect(Collectors.toList());
        tags.removeIf(p-> p.getFst().isEmpty());
        //separação de strings das tags
        List<Pair<String,Long>> tagsFinal = new ArrayList<>();
        for(Pair<String,Integer> p1 : tags) { // conta o numero de strings iguais
            tagsFinal.add(new Pair<>(p1.getFst(), tags.stream().filter(p -> p1.getFst().equals(p.getFst())).count()));
        }
        List<Pair> pairs = new ArrayList<>();
        // cria lista sem string repetidas e limita-as ao número dado
        for(Pair p : tagsFinal){
            if(!containsFirst(pairs,p)) pairs.add(p);
        }
        // coleciona os ids das N tags mais usadas no intervalo de tempo dado
        List<Pair<Long,Long>> res = new ArrayList<>();
        for(Pair tag : pairs)
            res.add(new Pair<Long,Long>(dados.getTag((String) tag.getFst()).getId(),(Long) tag.getSnd()));
        res.sort(new ComparatorTagsMaisUsadas());
        return res.stream().map(p->p.getFst()).limit(N).collect(Collectors.toList());
    }

    /**
     *
     * @param pairs lita de pares (string, contador de ocorrencias da string)
     * @param p par de (string, contador de ocorrencias da string)
     * @return return um boolean que indica se a string está na lista ou não
     */

    private static Boolean containsFirst(List<Pair> pairs, Pair p){
        for(Pair p1 : pairs){
            if(p1.getFst().equals(p.getFst())) return true;
        }
        return false;
    }
}
