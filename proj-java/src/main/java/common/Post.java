package main.java.common;

import java.time.LocalDate;

public class Post implements Comparable<Post>{

    private long id;
    private int tipo;
    private long userId;
    private long parentId;
    private String titulo;
    private String tags;
    private LocalDate data;
    private long answerCount;
    private int score;
    private int commentCount;
    private int upvotes;
    private int downvotes;

    /**
     * Construtor vazio para criar um objeto do tipo Post.
     */
    public Post(){
        this.id = 0;
        this.tipo = 0;
        this.userId = 0;
        this.parentId = 0;
        this.titulo = "";
        this.tags = "";
        this.data = LocalDate.now();
        this.answerCount = 0;
        this.score = 0;
        this.commentCount = 0;
        this.upvotes = 0;
        this.downvotes = 0;
    }

    /**
     * Construtor parametrizado para criar um objeto do tipo Post.
     *
     * @param id id do Post
     * @param tipo tipo do Post
     * @param userId userId do Post
     * @param parentId parentId do Post
     * @param titulo titulo do Post
     * @param tags tags do Post
     * @param data data do Post
     * @param answerCount answerCount do Post
     * @param score score do Post
     * @param commentCount commentCount do Post
     * @param upvotes upvotes do Post
     * @param downvotes downvotes do Post
     */
    public Post(long id, int tipo, long userId, long parentId, String titulo, String tags, LocalDate data, long answerCount, int score, int commentCount, int upvotes, int downvotes) throws ValoresInvalidosException{
        this.setId(id);
        this.setTipo(tipo);
        this.setUserId(userId);
        this.setParentId(parentId);
        this.setTitulo(titulo);
        this.setTags(tags);
        this.setData(data);
        this.setAnswerCount(answerCount);
        this.setScore(score);
        this.setCommentCount(commentCount);
        this.setUpvotes(upvotes);
        this.setDownvotes(downvotes);
    }

    /**
     * Construtor cópia para criar um objeto do tipo Post com os campos copiados de outro objeto do mesmo tipo.
     *
     * @param umPost Post a ser copiado
     */
    public Post(Post umPost) {
        this.id = umPost.getId();
        this.tipo = umPost.getTipo();
        this.userId = umPost.getUserId();
        this.parentId = umPost.getParentId();
        this.titulo = umPost.getTitulo();
        this.tags = umPost.getTags();
        this.data = umPost.getData();
        this.answerCount = umPost.getAnswerCount();
        this.score = umPost.getScore();
        this.commentCount = umPost.getCommentCount();
        this.upvotes = umPost.getUpvotes();
        this.downvotes = umPost.getDownvotes();
    }

    /**
     * Devolve o id do Post.
     *
     * @return retorna o id do Post
     */
    public long getId() {
        return id;
    }

    /**
     * Define o id do Post.
     *
     * @param id id do Post
     */
    public void setId(long id) {
        this.id = id;
    }

    /**
     * Devolve o tipo do Post.
     *
     * @return retorna o tipo do Post
     */
    public int getTipo() {
        return tipo;
    }

    /**
     * Define o tipo do Post.
     *
     * @param tipo tipo do Post
     * @throws ValoresInvalidosException caso o tipo seja negativo
     */
    public void setTipo(int tipo) throws ValoresInvalidosException{
        if (tipo < 0) throw new ValoresInvalidosException(Integer.toString(tipo));
        this.tipo = tipo;
    }

    /**
     * Devolve o userId do Post.
     *
     * @return retorna o userId do Post
     */
    public long getUserId() {
        return userId;
    }

    /**
     * Define o userId do Post.
     *
     * @param userId userId do Post
     */
    public void setUserId(long userId) {
        this.userId = userId;
    }

    /**
     * Devolve o parentId do Post.
     *
     * @return retorna o parentId do Post
     */
    public long getParentId() {
        return parentId;
    }

    /**
     * Define o parentId do Post.
     *
     * @param parentId parentId do Post
     */
    public void setParentId(long parentId) {
        this.parentId = parentId;
    }

    /**
     * Devolve o titulo do Post.
     *
     * @return retorna o titulo do Post
     */
    public String getTitulo(){
        return titulo;
    }

    /**
     * Define o titulo do Post.
     *
     * @param titulo titulo do Post
     * @throws ValoresInvalidosException caso o titulo seja (null) ou vazio
     */
    public void setTitulo(String titulo) throws ValoresInvalidosException{
        if (titulo == null) throw new ValoresInvalidosException("titulo=null");
        this.titulo = titulo;
    }

    /**
     * Devolve as tags do Post.
     *
     * @return retorna as tags do Post
     */
    public String getTags() {
        return tags;
    }

    /**
     * Define as tags do Post.
     *
     * @param tags tags do Post
     * @throws ValoresInvalidosException caso a tags seja (null) ou vazia
     */
    public void setTags(String tags) throws ValoresInvalidosException{
        if (tags == null) throw new ValoresInvalidosException("tags=null");
        this.tags = tags;
    }

    /**
     * Devolve a data do Post.
     *
     * @return retorna a data do Post
     */
    public LocalDate getData() {
        return data;
    }

    /**
     * Define a data do Post.
     *
     * @param data data do Post
     * @throws ValoresInvalidosException caso a data seja (null)
     */
    public void setData(LocalDate data) throws ValoresInvalidosException{
        if(data == null) throw new ValoresInvalidosException("data=null");
        this.data = data;
    }

    /**
     * Devolve a AnswerCount do Post.
     *
     * @return retorna a AnswerCount do Post
     */
    public long getAnswerCount() {
        return answerCount;
    }

    /**
     * Define a AnswerCount do Post.
     *
     * @param answerCount answerCountdo Post
     * @throws ValoresInvalidosException caso a answerCount seja negativa
     */
    public void setAnswerCount(long answerCount) throws ValoresInvalidosException{
        if (answerCount < 0) throw new ValoresInvalidosException(Long.toString(answerCount));
        this.answerCount = answerCount;
    }

    /**
     * Devolve o score do Post.
     *
     * @return retorna o score do Post
     */
    public int getScore() {
        return score;
    }

    /**
     * Define o score do Post.
     *
     * @param score score do Post
     */
    public void setScore(int score) {
        this.score = score;
    }

    /**
     * Devolve o commentCount do Post.
     *
     * @return retorna o commentCount do Post
     */
    public int getCommentCount() {
        return commentCount;
    }

    /**
     * Define o commentCount do Post.
     *
     * @return retorna o commentCount do Post
     * @throws ValoresInvalidosException caso o commentCount seja negativo
     */
    public void setCommentCount(int commentCount) throws ValoresInvalidosException{
        if (commentCount < 0) throw new ValoresInvalidosException(Integer.toString(commentCount));
        this.commentCount = commentCount;
    }

    /**
     * Devolve os upvotes do Post.
     *
     * @return retorna os upvotes do Post
     */
    public int getUpvotes() {
        return upvotes;
    }

    /**
     * Define os upvotes do Post.
     *
     * @param upvotes upvotes do Post
     * @throws ValoresInvalidosException caso o upVotes seja negativo
     */
    public void setUpvotes(int upvotes) throws ValoresInvalidosException{
        if (upvotes < 0) throw new ValoresInvalidosException(Integer.toString(upvotes));
        this.upvotes = upvotes;
    }

    /**
     * Devolve os downvotes do Post.
     *
     * @return retorna os downvotes do Post
     */
    public int getDownvotes() {
        return downvotes;
    }

    /**
     * Define os downvotes do Post.
     *
     * @param downvotes downvotes do Post
     * @throws ValoresInvalidosException caso o downVotes seja negativo
     */
    public void setDownvotes(int downvotes) throws ValoresInvalidosException{
        if (downvotes < 0) throw new ValoresInvalidosException(Integer.toString(downvotes));
        this.downvotes = downvotes;
    }

    /**
     * Devolve uma representação do objeto Post em formato String.
     *
     * @return retorna uma representação do objeto Post em formato String.
     */
    public String toString() {
        final StringBuilder sb = new StringBuilder("Post{");
        sb.append("id=").append(id);
        sb.append(", tipo=").append(tipo);
        sb.append(", userId=").append(userId);
        sb.append(", parentId=").append(parentId);
        sb.append(", titulo='").append(titulo).append('\'');
        sb.append(", tags='").append(tags).append('\'');
        sb.append(", data=").append(data);
        sb.append(", answerCount=").append(answerCount);
        sb.append(", score=").append(score);
        sb.append(", commentCount=").append(commentCount);
        sb.append(", upvotes=").append(upvotes);
        sb.append(", downvotes=").append(downvotes);
        sb.append("}\n\n\n\n\n\n");
        return sb.toString();
    }

    /**
     * Indica se os campos do objeto atual são iguais ao objeto argumento.
     *
     * @return retorna true caso o objeto atual seja igual ao objeto argumento; false caso contrário
     */
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Post post = (Post) o;
        return id == post.getId() &&
                tipo == post.getTipo() &&
                userId == post.getUserId()&&
                parentId == post.getParentId() &&
                answerCount == post.getAnswerCount() &&
                score == post.getScore() &&
                commentCount == post.getCommentCount() &&
                upvotes == post.getUpvotes() &&
                downvotes == post.getDownvotes() &&
                titulo.equals(post.getTitulo()) &&
                tags.equals(post.getTags()) &&
                data.equals(post.getData());
    }

    /**
     * Cria e retorna uma cópia do objeto atual.
     *
     * @return retorna uma cópia da instância atual
     */
    public Post clone(){
        return new Post(this);
    }

    /**
     * Adiciona um voto a um Post.
     *
     * @param vote vote do Post
     * @param post post do Post
     */
    public void addVoteToPost(int vote, Post post){
        if (vote == 2) this.upvotes++;
        else this.downvotes++;
    }

    /**
     * Devolve o saldo de votos (upvotes - downvotes) de um Post.
     *
     * @return retorna o saldo de votos
     */
    public int contaVotos(){
        return this.upvotes - this.downvotes;
    }

    /**
     * Compara o Post atual com um Post argumento por data.
     *
     * @param post post a ser comparado
     * @return fator de comparação
     */
    public int compareTo(Post post){
        if (post == null || post.getData().isEqual(this.data)) return 0;
        else if (post.getData().isBefore(this.data)) return 1;
        else return -1;
    }
}