class MySelectQuery
    def initialize(csv_content)
        #division de la chaine en ligne puis en valeurs
      @data = csv_content.split("\n").map{|line| line.split(",")} 
        #extraction de l'entete et transformation de chaque valeur d'entete en colonne
      @header = @data.shift.map { |head| head.downcase }
    end
  
    def where(column_name,criteria)
        #selection de l'indice concerner
      
      cible = @header.index(column_name.downcase)
        #si la la colonne en question n'hexiste pas
      if (cible.nil?) 
        return []
      end

      resultat = @data.select { |line| line[cible].include?(criteria) }
      resultat.map { |line| line.join(",") } 
  end
end
  

  