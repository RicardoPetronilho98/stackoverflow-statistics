package main.java.engine;


import main.java.common.*;

/**
 * Dado o identificador de um post, a fun¸c˜ao deve retornar
 * o t´ıtulo do post e o nome (n˜ao o ID) de utilizador do autor;
 */
public class Q1 {

    /**
     *
     * @param dados base de dados com toda a informação do sistema
     * @param id id do post a ser procurado
     * @return retorna um par com o titulo da pergunta e o id do user que a fez
     * @throws PostNaoExisteException retorna a excepção de inesistencia do post
     * @throws IdNegativoException retorna erro de introdução de id negativo
     */
    public static Pair<String,String> infoFromPost(Dados dados, long id) throws PostNaoExisteException,IdNegativoException,UserNaoExisteException {
        if(id < 0)  throw new IdNegativoException("Id de Post negativo");
        Pair<String,String> resposta = new Pair<>(null, null);
        Post post;
        post = dados.getPost(id);
        if(post.getTipo() == 1){
            resposta = new Pair<>(post.getTitulo(),dados.getUser(post.getUserId()).getNome());
        }
        if(post.getTipo() == 2){
            post = dados.getPost(post.getParentId());
            resposta = new Pair<>(post.getTitulo(),dados.getUser(post.getUserId()).getNome());
        }
        return resposta;
    }
}
