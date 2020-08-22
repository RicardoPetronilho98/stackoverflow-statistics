package main.java.common;
/**
 @file tags.c
 Módulo que contém as funções de criação, manipulação e destruição de uma tag.
 */

public class Tag {
    private long id;
    private String nome;

    /**
     * Construtor vazio
     */
    public Tag(){
        this.id = 0;
        this.nome = "";
    }

    /**
     *@param id - id da tag
     *@param nome - nome da tag
     */

    public Tag(long id, String nome) throws ValoresInvalidosException{
        this.setId(id);
        this.setNome(nome);
    }

    /**\brief Construtor da tag
     * @param umaTag informação de uma tag
     */

    public Tag(Tag umaTag){
        this.id = umaTag.getId();
        this.nome = umaTag.getNome();
    }

    /**
     * @return NULL caso a tag não esja inicializada ou o id da tag
     */

    public long getId(){

        return this.id;
    }

    /**
     * @return retorna o nome
     */

    public String getNome()
    {
        return this.nome;
    }

    /**
     * @param id id a ser guardado na tag
     */

    public void setId(long id){

        this.id = id;
    }

    /**
     * @param nome - nome a ser guardado na tag
     */

    public void setNome(String nome) throws ValoresInvalidosException{
        if(nome == null || nome.isEmpty()) throw new ValoresInvalidosException(nome);
        this.nome = nome;
    }

    /**
     * @return um clone do objeto tag
     */

    public Tag clone(){

        return new Tag(this);
    }

    /**
     * @return uma string com a informação de uma tag
     */
    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder("Tag{");
        sb.append("id=").append(id);
        sb.append(", nome='").append(nome).append('\'');
        sb.append("}\n\n\n\n\n\n");
        return sb.toString();
    }

    /**
     * @param object a ser comparado com a tag em questão
     * @return boolean com resultado da comparação
     */

    public boolean equals(Object object) {
        if (this == object) return true;
        if (!(object instanceof Tag) || object == null) return false;
        Tag tags = (Tag) object;
        return this.getId() == tags.getId() &&
                this.getNome() == tags.getNome();
    }

}