require 'sinatra'
require 'json'
require_relative 'my_user_model.rb'

set :bind, '0.0.0.0'
set :port, 8080
enable :sessions

# post "/hi" do 
#     response ='Bonjour le monde rochnel'
#     puts response
# end

get '/' do
    redirect 'views/index.html'
end

get '/users' do
    content_type = json
    users = User.all  
    return users.map{|user| user.reject{|k,_| k == password }}.to_json
end

post '/users' do
        # firstname = params[:firstname]
        # lastname = params[:lastname]
        # age = params[:age].to_i
        # password = params[:password]
        # email = params[:email]
        content_type = json
        user_info = JSON.parse(request.body.read)
        user = User.new
        user_id = user.create(user_info)

        user_created = user.find(user_id).reject{|k,_| k == password}.to_json
        return user_created
end

post'/sign_in' do
    password = params[:password]
    email = params[:email]

    content_type = json
    user_id = session[:user_id]

    # db = SQLite3::Database.open('maDataBase.db')
    # db.results_as_hash = true
    # requette = <<-SQL
    #     SELECT id FROM users WHERE email = ?
    # SQL
    # user_id = db.execute(requette, email);

    if user_id    
        user_search = User.find(user_id)
    end

    return user_created.reject{|k,_| k == password}.to_json

end

put '/users' do

    content_type = json
    user_id = session[:user_id]
    if user_id
       resset_password = params[:password]
    end
    
    user_search = User.update(user_id, "password", resset_password)
    return user_reset.reject{|k,_| k == password}.to_json
end

delete '/sign_out' do
    user_id = session[:user_id]

    if user_id
        session.delete(:user_id)
        halt 204
    end
end

delete '/users' do
    user_id = session[:user_id]

    if user_id
        user = new User
        user_found = user.find(user_id)
        user.destroy(user_id)

        halt 204
    end
end




#   curl -X POST -i https://gb46b1e2c-b99e.docode.fi.qwasar.io/hi