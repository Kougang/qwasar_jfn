require 'sqlite3'

class User
    attr_accessor :id, :firstname,:lastname, :age, :password, :email
    def initialize(id, firstname,lastname, age, password, email)
        @id = id
        @firstname = firstname
        @lastname = lastname
        @age = age
        @password = password
        @email = email 
    end


    def self.create(user_info)
        db = SQLite3::Database.open('db.sql')
        db.results_as_hash = true

        db.execute <<-SQL
        CREATE TABLE IF NOT EXISTS users(
            id INTEGER PRIMARY KEY,
            firstname TEXT,
            lastname TEXT,
            age INTEGER,
            password TEXT,
            email TEXT);      
        SQL

        requette = <<-SQL
            INSERT INTO users (firstname,lastname, age, password, email) VALUES (?, ?, ?, ?, ?)
        SQL
        # 
        db.execute(requette, user_info.values); # return the arr of hash
        user_id = db.last_insert_row_id

        user = db.execute('SELECT * FROM users WHERE id = ?', user_id)
         db.close()       
         User.new(user[0]["id"], user[0]["firstname"], user[0]["lastname"], user[0]["age"], user[0]["password"], user[0]["email"])
    end

    def self.find(user_id)
        db = SQLite3::Database.open('db.sql')
        db.results_as_hash = true

        requette = <<-SQL
            SELECT * FROM users WHERE id = ?
        SQL
        user = db.execute(requette, user_id.to_i); # return the arr of hash

        db.close()

       return User.new(user[0]["id"], user[0]["firstname"], user[0]["lastname"], user[0]["age"], user[0]["password"], user[0]["email"])
       
    end

    def self.all
        db = SQLite3::Database.open('db.sql')
        users = db.execute("SELECT * FROM users");
        # return the array of arrays result
        db.close()
        return users
    end

    def self.update(user_id , attribute , value )
        db = SQLite3::Database.open('db.sql')

        requette = <<-SQL
            UPDATE users SET #{attribute} = ? WHERE id = ?
        SQL
        user = db.execute(requette, value, user_id.to_i);
         
        user_hash = User.find(user_id.to_i)
        db.close()

        return user_hash
    end
    def self.destroy(user_id)
        db = SQLite3::Database.open('db.sql')
        requette = <<-SQL
            DELETE FROM users WHERE id = ?
        SQL
        user_deleted = db.execute(requette,user_id.to_i);
        db.close()
    end
    def self.auth(password,email)
        # puts "dans auth"
        db = SQLite3::Database.open('db.sql')
        db.results_as_hash = true

        # puts "ouverture database"
        requette = <<-SQL
        SELECT * FROM users WHERE password = ? AND email = ?
        SQL
        user = db.execute(requette,[password,email]);
        # puts "selection"
        db.close

        # # puts "retourn utilisateeur"
        # return User.new(user[0]["id"].to_i, user[0]["firstname"], user[0]["lastname"], user[0]["age"], user[0]["password"], user[0]["email"])
        return user
    end

end
