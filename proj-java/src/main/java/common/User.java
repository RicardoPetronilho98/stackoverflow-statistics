package main.java.common;
import java.util.List;
import java.util.ArrayList;

public class User{

	private long id;
    private int reputacao;
	private String nome;
	private String bio;
	private List<Long> postsIds;
	private int upVotes;
	private int downVotes;
	private int numeroPosts;    //  para esta contagem só entram perguntas e respostas

    /**
	 * Construtor vazio.
	 */
	public User() {
	    this.id = -2;
		this.reputacao = 0;
		this.nome = "";
		this.bio = "";
		this.postsIds = new ArrayList<Long>();
		this.upVotes = 0;
		this.downVotes = 0;
		this.numeroPosts = 0;
	}

	/**
	 * Construtor parametrizado.
     * @param id id do utilizador
	 * @param reputacao reputação do utilizador
	 * @param nome nome do utilizador
	 * @param bio biografia do utilizador
	 * @param postsIds	ids dos posts deste utilizador
	 * @param upVotes	votos positivos deste utilizador
	 * @param downVotes	votes negativos deste utilizador
	 * @param numeroPosts número de posts do utilizador
	 */
	public User(long id, int reputacao, String nome, String bio, List<Long> postsIds, int upVotes, int downVotes, int numeroPosts) throws ValoresInvalidosException{
		this.setId(id);
	    this.setReputacao(reputacao);
		this.setNome(nome);
		this.setBio(bio);
		this.setPostsIds(postsIds);
		this.setUpVotes(upVotes);
		this.setDownVotes(downVotes);
		this.setNumeroPosts(numeroPosts);
	}

	/**
	 * Construtor cópia.
	 * @param umUser um utilizador
	 */
	public User(User umUser){
	    this.setId(umUser.getId());
		this.reputacao = umUser.getReputacao();
		this.nome = umUser.getNome();
		this.bio = umUser.getBio();
		this.postsIds = umUser.getPostsIds();
		this.upVotes = umUser.getUpVotes();
		this.downVotes = umUser.getDownVotes();
		this.numeroPosts = umUser.getNumeroPosts();
	}

    /**
     * Devolve o id do utilizador.
     * @return retorna o id do utilizador
     */
    public long getId() {
        return id;
    }

	/**
	 * Devolve a reputação deste utilizador.
	 * @return retorna a reputação deste utilizador
	 */
	public int getReputacao() {
		return reputacao;
	}

	/**
	 * Devolve o nome deste utilizador.
	 * @return retorna o nome deste utilizador
	 */
	public String getNome() {
		return nome;
	}

	/**
	 * Devolve a biografia deste utilizador
	 * @return retorna a biografia deste utilizador
	 */
	public String getBio() {
		return bio;
	}

	/**
	 * Devolve os ids dos posts deste utilizador.
	 * @return retorna os ids dos posts deste utilizador
	 */
	public List<Long> getPostsIds() {
		return new ArrayList<>(postsIds);
	}

	/**
	 * Devolve os votos positivos deste utilizador.
	 * @return retorna os votos positivos deste utilizador
	 */
	public int getUpVotes() {
		return upVotes;
	}

	/**
	 * Devolve os votos negativos deste utilizador.
	 * @return retorna os votos positivos deste utilizador
	 */
	public int getDownVotes() {
		return downVotes;
	}

    /**
     * Coloca o id do utilizador.
     * @param id id do utilizador
     */
    public void setId(long id){
        this.id = id;
    }

	/**
	 * Devolve o número de perguntas deste utilizador.
	 * @return retorna o número de perguntas deste utilizador
	 */
	public int getNumeroPosts() {
		return numeroPosts;
	}

	/**
	 * Coloca o número de perguntas deste utilizador.
	 * @param numeroPosts número de perguntas
     * @throws ValoresInvalidosException caso o número de Posts seja negativo
	 */
	public void setNumeroPosts(int numeroPosts) throws ValoresInvalidosException{
	    if (numeroPosts < 0) throw new ValoresInvalidosException(Integer.toString(numeroPosts));
		this.numeroPosts = numeroPosts;
	}

	/**
	 * Coloca a reputação deste utilizador.
	 * @param reputacao reputação deste utilizador
	 */
	public void setReputacao(int reputacao) {
		this.reputacao = reputacao;
	}

	/**
	 * Coloca o nome deste utilizador.
	 * @param nome nome deste utilizador
     * @throws ValoresInvalidosException caso o nome seja (null) ou vazio
	 */
	public void setNome(String nome) throws ValoresInvalidosException{
        if (nome == null || nome.isEmpty()) throw new ValoresInvalidosException(nome);
		this.nome = nome;
	}

	/**
	 * Coloca a biografia deste utilizador.
	 * @param bio biografia deste utilizador
     * @throws ValoresInvalidosException caso a bio seja (null)
	 */
	public void setBio(String bio) throws ValoresInvalidosException{
        if (bio == null) throw new ValoresInvalidosException("bio=null");
		this.bio = bio;
	}

	/**
	 * Coloca os ids dos posts deste utilizador.
	 * @param postsIds ids dos posts deste utilizador
	 */
	public void setPostsIds(List<Long> postsIds) {
		this.postsIds = new ArrayList<>(postsIds);
	}

	/**
	 * Coloca os votos positivos deste utilizador.
	 * @param upVotes votos positivos deste utilizador
     * @throws ValoresInvalidosException caso o número de upVotes seja negativo
	 */
	public void setUpVotes(int upVotes) throws ValoresInvalidosException{
        if (upVotes < 0) throw new ValoresInvalidosException(Integer.toString(upVotes));
		this.upVotes = upVotes;
	}

	/**
	 * Coloca os votos negativos deste utilizador.
	 * @param downVotes votos negativos deste utilizador
     * @throws ValoresInvalidosException caso o número de downVotes seja negativo
	 */
	public void setDownVotes(int downVotes) throws ValoresInvalidosException{
        if (downVotes < 0) throw new ValoresInvalidosException(Integer.toString(downVotes));
		this.downVotes = downVotes;
	}

	/**
	 * Devolve uma String com toda a informação deste objeto.
	 * @return retorna uma String com toda a informação deste objeto.
	 */

	@Override
	public String toString() {
		final StringBuilder sb = new StringBuilder("User{");
		sb.append("id=").append(id);
		sb.append(", reputacao=").append(reputacao);
		sb.append(", nome='").append(nome).append('\'');
		sb.append(", bio='").append(bio).append('\'');
		sb.append(", postsIds=").append(postsIds);
		sb.append(", upVotes=").append(upVotes);
		sb.append(", downVotes=").append(downVotes);
		sb.append(", numeroPosts=").append(numeroPosts);
		sb.append("}\n\n\n\n\n\n");
		return sb.toString();
	}

	/**
     * Devolve uma cópia deste objeto.
     * @return retorna uma cópia deste objeto
     */
	public User clone(){
		return new User(this);
	}

    /**
     * Verifica se o objeto recebido como parâmetro é igual a este objeto.
     * @param o objeto
     * @return returna true se forem iguais e false caso contrário
     */
	public boolean equals(Object o){
		if(this == o)return true;

		if(o == null || this.getClass() != o.getClass())return false;

		User umUser = (User) o;

		return this.id == umUser.getId() &&
				this.reputacao == umUser.getReputacao() &&
				this.nome.equals(umUser.getNome()) &&
				this.bio.equals(umUser.getBio()) &&
				this.postsIds.equals(umUser.getPostsIds()) &&
				this.upVotes == umUser.getUpVotes() &&
				this.downVotes == umUser.getDownVotes() &&
				this.numeroPosts == umUser.getNumeroPosts();
	}

	/**
	 * Adiciona o id de um post deste utilizador.
	 * @param id id do post
	 */
	public void add(Long id){
		this.postsIds.add(id);
	}

    /**
     * Devolve o saldo de votos (upVotes - downVotes) do User.
     * @return retorna o saldo de votos
     */
    public int contavotos(){
        return this.upVotes - this.downVotes;
    }

    /**
     * Incrementa o número de posts, indicando o tipo do post.
     * @param tipo tipo do post
     */
    public void incrementaNumeroPosts(int tipo){
        if (tipo == 1 || tipo == 2) this.numeroPosts++;
    }
}
