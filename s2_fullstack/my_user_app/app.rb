require 'sinatra'
require 'json'
require_relative 'my_user_model.rb'

set :bind, '0.0.0.0'
set :port, 8080
enable :sessions

get '/' do
    @users = User.all
    erb :index
end

get '/users' do
    content_type :json
    users = User.all  
    return users.map{|user| user.reject{|k,_| k == "password "}}.to_json
end

post '/users' do
    if params[:firstname]
        # user_info = JSON.parse(request.body.read)
        user = User.create(params)
        user_id = user.id
        user_created = User.find(user_id)
        user={:firstname=>user_created.firstname,:lastname=>user_created.lastname,:age=>user_created.age,:password=>user_created.password,:email=>user_created.email}.to_json    
    else
        user_param = User.auth(params[:password],params[:email])
        # puts "identifiant de l'utilisateur",user_param.id
        if user_param.empty?
            status 401
        else
            status 200
            session[:user_id] = user_param[0]["id"]
        end
        user_param[0].to_json
    end
end

post '/sign_in' do
   
    user_param = User.auth(params[:password],params[:email])
    # puts "identifiant de l'utilisateur",user_param.id
    if user_param.empty?
        status 401
    else
        status 200
        session[:user_id] = user_param[0]["id"]
    end
    user_param[0].to_json
end

put '/users' do
    id = session[:user_id]
    pwd = params[:password]
    User.update(id,'password',pwd)
    user_found=User.find(id)
    status 200
    user={:firstname=>user_found.firstname,:lastname=>user_found.lastname,:age=>user_found.age,:password=>user_found.password,:email=>user_found.email}.to_json    

  
end

delete '/sign_out' do 
    id = session[:user_id]
    if id
      session.delete(user_id)
    else
        status 401
    end
  end
  
  delete '/users' do 
    id = session[:user_id]
    if id
      session.destroy(id)
      session.delete(user_id)
    else
        status 401
     end
  end
