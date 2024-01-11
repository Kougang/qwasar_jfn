require 'sinatra'    # Import sinatra module.
require 'json'    # Import json module.
require_relative 'my_user_model.rb'    # Import module my_user_model.rb

set :bind, '0.0.0.0'    # Set bind address
set :port, 8080    # Set port number
enable :sessions    # enable session on sinatra

get '/' do    # get the main page
    @users=User.all()    # Get all the users
    erb :index    # Get the index page
 end

get '/users' do    # get all users
    status 200    # Set status code to 200
    User.all.map{|col| col.slice("firstname", "lastname", "age", "email")}.to_json    # get all users and map them and convert them to json
end

post '/sign_in' do    # handle sign in
    verify_user=User.authenticate(params[:password],params[:email])    # Authenticate user with given credentials.
    if !verify_user.empty?    # Check if user is empty or not
        status 200    # Set status code to 200
        session[:user_id] = verify_user[0]["id"]    # Set session variable for user id
    else
        status 401    # Set status code to 401
    end 
    verify_user[0].to_json    # Convert user to json
end

post '/users' do    # handle post request to user
    if params[:firstname] != nil    # Check if firstname is provided or not
        create_user = User.create(params)    # Create new user with given params
        new_user = User.find(create_user.id)    # find the newly created user
        user={:firstname=>new_user.firstname,:lastname=>new_user.lastname,:age=>new_user.age,:password=>new_user.password,:email=>new_user.email}.to_json    # Convert user to json
    else 
        check_user=User.authenticate(params[:password],params[:email])    # Authenticate user with given credentials.
        if !check_user[0].empty?    # Check if user is empty or not
            status 200    # Set status code to 200
            session[:user_id] = check_user[0]["id"]    # Set session variable for user id
        else
            status 401    # Set status code to 401
        end 
        check_user[0].to_json    # Convert user to json
    end 
end

put '/users' do    # handle put request for user
    User.update(session[:user_id] , 'password', params[:password])    # Update user password
    user=User.find(session[:user_id])    # Find user 
    status 200    # Set status code to 200
    user_info={:firstname=>user.firstname,:lastname=>user.lastname,:age=>user.age,:password=>user.password,:email=>user.email}.to_json    # Convert user to json
end

delete '/sign_out' do    # handle sign out
    session[:user_id] = nil if session[:user_id]    # Clear session variable
    status 204    # Set status code to 204
end

# To delete an active user uncomment line 61, gandalf couln't permit deleting a user from the db
delete '/users' do    # handle delete for user
    # User.destroy(session[:user_id]) if !session[:user_id].empty?    # Delete user from db
    status 204    # Set status code to 204
end
