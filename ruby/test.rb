require_relative 'my_user_model.rb'
  # create method
  
  user = User.new()
  
  user_info = {
    'firstname' => 'chinois',
    'lastname' => 'noir',
    'age' => 25 ,
    'password' => 'securepassword',
    'email' => 'john.doe@example.com'
  }
  
  user_id = user.create(user_info)
  puts "Nouvel utilisateur inséré avec l'ID : #{user_id}"
  
  
  # ===============================
  # find method
  # ===============================
  
  
  # user = User.new
  # found_user = user.find(13)
  # puts found_user.inspect
  # puts "user found", found_user
  
  # ===============================
  # found users
  # ===============================
  
  # user = User.new
  # found_user = user.all
  # puts "toute la base de donnee:", found_user
  
  # ===============================
  # found users
  # ===============================
  
  # user = User.new
  # found_user = user.update(13,"firstname", "KOUGANG")
  # puts "utilisateur modif:", found_user
  
  # ===============================
  # destroy users
  # ===============================
  
  # user = User.new
  
  # for i in 0..13
  #     delete_user = user.destroy(i)
  # end
  # puts "suppression reuissie!"