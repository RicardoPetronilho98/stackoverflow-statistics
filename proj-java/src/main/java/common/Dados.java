package main.java.common;

import main.java.engine.ComparatorPostData;

import java.io.IOException;
import java.io.PrintWriter;
import java.time.LocalDate;
import java.util.*;
import java.lang.Long;
import java.util.stream.Collectors;

public class Dados {

    private Map<Long, User> users;
    private Map<Long, Post> posts;
    private Map<String, Tag> tags;

    /**
     * Construtor vazio.
     */
    public Dados(){
        this.users = new HashMap<>();
        this.posts = new HashMap<>();
        this.tags = new HashMap<>();
    }

    /**
     * Construtor parametrizado.
     * @param users utilizadores
     * @param posts posts dos utilizadores
     * @param tags tags dos posts
     */
    public Dados(Map<Long, User> users, Map<Long, Post> posts, Map<String, Tag> tags) {
        this.setUsers(users);
        this.setPosts(posts);
        this.setTags(tags);
    }

    /**
     * Construtor cópia.
     * @param dados base de dados
     */
    public Dados(Dados dados){
        this.setUsers(dados.getUsers());
        this.setPosts(dados.getPosts());
        this.setTags(dados.getTags());
    }

    /**
     * Devolve os users da base de dados.
     * @return retorna os users da base de dados
     */
    public Map<Long, User> getUsers() {
        HashMap<Long,User> clone = new HashMap<Long, User>();
        for(Map.Entry<Long,User> entry: this.users.entrySet())
            clone.put(entry.getKey(), entry.getValue().clone());
        return clone;
    }

    /**
     * Coloca os users na base de dados no sistema.
     * @param users utilizadores da base de dados
     */
    public void setUsers(Map<Long, User> users) {
        this.users = new HashMap<Long, User>();
        for(Map.Entry<Long,User> entry: users.entrySet())
            this.users.put(entry.getKey(), entry.getValue().clone());
    }

    /**
     * Devolve os posts da base de dados.
     * @return retorna os posts da base de dados
     */
    public Map<Long, Post> getPosts() {
        Map<Long,Post> clone = new HashMap<>();
        for(Map.Entry<Long,Post> entry: this.posts.entrySet())
            clone.put(entry.getKey(), entry.getValue().clone());
        return clone;
    }

    /**
     * Coloca os posts na base de dados.
     * @param posts posts dos utilizadores
     */
    public void setPosts(Map<Long, Post> posts) {
        this.posts = new HashMap<>();
        for(Map.Entry<Long,Post> entry : posts.entrySet())
            this.posts.put(entry.getKey(), entry.getValue().clone());
    }

    /**
     * Devolve as tags da base de dados.
     * @return retorna as tags da base de dados
     */
    public Map<String, Tag> getTags() {
        HashMap<String,Tag> clone = new HashMap<String, Tag>();
        for(Map.Entry<String,Tag> entry: this.tags.entrySet())
            clone.put(entry.getKey(), entry.getValue().clone());
        return clone;
    }

    /**
     * Coloca as tags na base de dados.
     * @param tags tags dos posts
     */
    public void setTags(Map<String, Tag> tags) {
        this.tags = new HashMap<String, Tag>();
        for(Map.Entry<String,Tag> entry :tags.entrySet())
            this.tags.put(entry.getKey(), entry.getValue().clone());
    }

    /**
     * Devolve a String com toda a informação deste objeto.
     * @return retorna uma String com toda a informação
     */
    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("Dados{");
        sb.append("users=").append(users);
        sb.append(", posts=").append(posts);
        sb.append(", tags=").append(tags);
        sb.append('}');
        return sb.toString();
    }

    /**
     * Devolve uma cópia deste objeto.
     * @return retorna uma cópia deste objeto
     */
    public Dados clone(){
        return new Dados(this);
    }

    /**
     * Verifica se o objeto recebido como parâmetro é igual a este objeto.
     * @param o objeto
     * @return return true se forem iguais e false caso contrário
     */
    public boolean equals(Object o){

        if(this == o) return true;

        if(o == null || this.getClass() != o.getClass()) return false;

        Dados dados = (Dados) o;

        return this.users.equals(dados.getUsers()) &&
                this.posts.equals(dados.getTags()) &&
                this.tags.equals(dados.getTags());
    }


    /**
     * Adiciona um user aos dados.
     * @param user utilizador
     */
    public void add(User user) throws UserExisteException{
        if(this.users.containsKey(user.getId())) throw new UserExisteException(Long.toString(user.getId()));
        this.users.put(user.getId(), user.clone());
    }

    /**
     * Adiciona um post à base de dados.
     * @param post post de um utilizador
     */
    public void add(Post post) throws PostExisteException{
        if(this.posts.containsKey(post.getId())) throw new PostExisteException(Long.toString(post.getId()));
        this.posts.put(post.getId(), post.clone());
    }

    /**
     * Adiciona uma tag à base de dados
     * @param tag tag de um post
     */
    public void add(Tag tag) throws TagExisteException{
        if(this.tags.containsKey(tag.getId())) throw new TagExisteException(Long.toString(tag.getId()));
        this.tags.put(tag.getNome(),tag);
    }

    /**
     * Devolve a informação do utilizador com o id indicado como parâmetro.
     * @param id id do utilizador
     * @return retorna a informação do utilizador com o id indicado como parâmetro
     */
    public User getUser(Long id) throws UserNaoExisteException{
        if(!this.users.containsKey(id)) throw new UserNaoExisteException(Long.toString(id));
        return this.users.get(id).clone();
    }

    /**
     * Devolve a informação do Post com o id indicado como parâmetro.
     * @param id id do post
     * @return retorna a informação do Post com o id indicado como parâmetro.
     */
    public Post getPost(Long id) throws PostNaoExisteException{
        if(!this.posts.containsKey(id)) throw new PostNaoExisteException(Long.toString(id));
        return this.posts.get(id).clone();
    }


    public Tag getTag(String nome) throws TagNaoExisteException{
        if(!this.tags.containsKey(nome)) throw new TagNaoExisteException(nome);
        return this.tags.get(nome);
    }

    /**
     * Escreve os dados num ficheiro.
     *
     * @param filename nome do ficheiro
     * @throws IOException
     */
    public void writeOnFile(String filename) throws IOException {
        PrintWriter fich = new PrintWriter(filename);
        fich.println(this);
        fich.flush();
        fich.close();
    }

    /**
     * Adiciona o id de um Post a um ulizador.
     *
     * @param userId id do utilizador
     * @param postId id do post
     */
    public void add(Long userId, Long postId, int tipo){
        this.users.get(userId).add(postId);
        this.users.get(userId).incrementaNumeroPosts(tipo);
    }

    /**
     * Devolve uma coleção de posts ordenado por data de criação dentro do intervalo de tempo especificado.
     *
     * @param inicio data de inicio do intervalo de tempo
     * @param fim data do fim do intervalo de tempo
     * @return retorna uma coleção de posts ordenada
     */
    public Collection<Post> getPostsPorDataCollection(LocalDate inicio, LocalDate fim){
        return this.getPosts().values().stream().filter(post -> !post.getData().isBefore(inicio) && !post.getData().isAfter(fim)).sorted(new ComparatorPostData()).collect(Collectors.toCollection(ArrayList::new));
    }

    /**
     * Devolve uma coleção de users que postaram dentro do intervalo de tempo especificado.
     *
     * @param inicio data de inicio do intervalo de tempo
     * @param fim data do fim do intervalo de tempo
     * @return retorna uma coleção de users
     */
    public Collection<User> getUsersPorDataCollection(LocalDate inicio, LocalDate fim){
        return this.getUsers().values().stream().filter(user -> {
            for(Long id: user.getPostsIds()){
                try{
                    Post post = this.getPost(id);
                    if (!post.getData().isBefore(inicio) && !post.getData().isAfter(fim)) return true;
                } catch (PostNaoExisteException e) {
                    e.printStackTrace();
                    System.out.println("Erro: ocorreu um erro interno no método getUsersPorDataCollection() - Post não encontrado!");
                    System.exit(-1);
                }
            }
            return false;
        }).collect(Collectors.toCollection(ArrayList::new));
    }
}
