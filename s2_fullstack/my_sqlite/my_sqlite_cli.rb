require 'date'
require_relative 'my_sqlite_request'

class MySqliteCLI
  KEYWORDS = %w[select insert update delete from join where order values set]

  def initialize(database)
    @database = database
    ARGV.clear
    run
  end

  def run
    first_MSG
    loop do
      print 'my_sqlite_cli>'
      input = gets.chomp #
      if input == 'quit'
        break 
      end  
    #   organize the input in array
      input_parsed_array = inputParse(input)
      action(input_parsed_array)
    end
  end

  private

  def action(input)
    request_sql = MySqliteRequest.new
    while !input.empty?
      case input[0].upcase
      when 'SELECT'
        select(request_sql, input)
      when 'INSERT'
        insert(request_sql, input)
    #   when 'UPDATE'
    #     handle_update(request_sql, input)
      when 'DELETE'
        delete(request_sql, input)
      when 'FROM'
        from(request_sql, input)
    #   when 'JOIN'
    #     handle_join(request_sql, input)
      when 'WHERE'
        where(request_sql, input)
    #   when 'ORDER'
    #     handle_order(request_sql, input)
      when 'VALUES'
        values(request_sql, input)
    #   when 'SET'
    #     handle_set(request_sql, input)
      else
        puts 'syntax wrong'
      end
    end
    request_run(request_sql)
  end

  def from(request_sql, input)
    remove_quotations(input[1])
    # call the from methode in my_sqlite_request and give him the attribut
    request_sql.from(input[1])
    input.shift(2) #remove 
  end

  def select(request_sql, input)
    column = []
    loop do
      input.shift
      if input.first.end_with?(',')
        column << input.first[0...-1]
      else
        column<< input.first
        break
      end
    end
    input.shift
    column.each { |col| remove_quotations(col) }
    request_sql.select(*column)
  end

  def insert(request_sql, input)
    raise "Must be INSERT INTO" unless input[1].upcase == 'INTO'

    remove_quotations(input[2])
    request_sql.insert(input[2])
    input.shift(3)
  end

  def handle_update(request_sql, input)
    remove_quotations(input[1])
    request_sql.update(input[1])
    input.shift(2)
  end

  def delete(request_sql, input)
    request_sql.delete
    input.shift
  end

  def handle_join(request_sql, input)
    raise 'Invalid join syntax' if input[5].nil? || 
                                   input[2].upcase != 'ON' || 
                                   input[4] != '='
            
    table_b = input[1]
    col_a = input[3]
    col_b = input[5]
    [col_a, table_b, col_b].each { |col| remove_quotations(col) }
    request_sql.join(col_a, table_b, col_b)
    input.shift(6)
  end

  def handle_order(request_sql, input)
    raise 'Invalid order syntax' if input[1].upcase != 'BY' || input[2].nil?

    col_name = remove_quotations(input[2])
    shift = 3
    order = remove_quotations(input[3].upcase) if input[3]
    if %w[ASC DESC].include?(order)
      request_sql.order(col_name, order)
      shift += 1
    else
      request_sql.order(col_name)
    end
    input.shift(shift)
  end

  def values(request_sql, input)
    values = []
    raise 'Invalid values syntax' unless input[1] == '('
    input.shift
    while true
      input.shift
      raise 'Invalid values syntax' unless input[0][-1] == ',' || input[0][-1] == ')'

      values << remove_quotations(input.first[0...-1])
      break unless input.first.end_with?(',')
    end
    input.shift
    request_sql.values(*values)
  end

  def handle_set(request_sql, input)
    data = {}
    input.shift
    while true
      col = input[0]
      raise 'Invalid syntax' unless input[1] == '='

      if input[2].end_with?(',')
        val = remove_quotations(input[2][0...-1])
        data[col] = val
        input.shift(3)
      else
        val = remove_quotations(input[2])
        data[col] = val
        input.shift(3)
        break
      end
    end
    request_sql.set(data)
  end

  def where(request_sql, input)
    input.shift
    where_type = input[1].upcase
    if where_type == '='
      second_where(request_sql, input)
    elsif where_type == 'IN'
      multi_where(request_sql, input)
    else
      raise 'Invalid syntax'
    end
  end

  def second_where(request_sql, input)
    column = input[0]
    criteria = input[2]
    if criteria.nil?
        puts 'no valide value criteria' 
    end

    [column, criteria].each { |col| remove_quotations(col) }
    request_sql.where(column, criteria)
    input.shift(3)
  end

  # Where/Values has an extra skip since ( is separated
  def multi_where(request_sql, input)
    criterias = []
    col_name = input.first
    raise 'Invalid where syntax' if input[2] != '('
    input.shift(3)

    while true
      raise 'Invalid values syntax' unless input[0][-1] == ',' || input[0][-1] == ')'

      criterias << remove_quotations(input.first[0...-1])
      break unless input.first.end_with?(',')
    
      input.shift
    end
    input.shift
    remove_quotations(col_name)
    request_sql.where(col_name, criterias)
  end

  def request_run(request_sql)
    # print the result if it's an select option and execute correctly another cases
    request_sql.type_of_query == :select ? results_ouput(request_sql.run) : request_sql.run
  end

  def results_ouput(selected)
    selected.each do |result| 
      result.values.each_with_index do |val, i|
        print val
        if i == (result.length - 1)
          print "\n"
        else
          print '|'
        end
      end
    end
  end

  def inputParse(inp)
    request_sqluest_end = inp[-1]

    if request_sqluest_end != ';'
     puts "finish query be ;"
    end

    line = add_space(inp[0...-1]) #except last element semicolon
    CSV.parse_line(line, col_sep: ' ', quote_char: "'", liberal_parsing: true)
  end

  # insert space after single parenthesis
  def add_space(line)
    pile = []
    line.each_char.with_index do |cha, i|
      if cha == "'"
        pile.empty? ? pile << cha : pile.pop
      elsif cha == '(' && pile.empty?
          line[i] = '( '
          break
      end
    end
    line
  end

  def remove_quotations(col)
    col[0] = '' if col[0] == "'" || col[0] == '"'
    col[-1] = '' if col[-1] == "'" || col[-1] == '"'
    col
  end

  def first_MSG
    puts "MySQLite version 0.1 #{Date.today}"
  end
#   select succes: SELECT name FROM nba_player_data.csv
#   delete first success: case DELETE FROM 'nba_player_data.csv'
#   delete second success: DELETE FROM 'nba_player_data.csv' WHERE name = 'Kareem Abdul-Jabbar';
# 

end

if __FILE__ == $PROGRAM_NAME
  MySqliteCLI.new(ARGV[0])
end


# INSERT INTO 'nba_player_data.csv' (name, year_start, year_end, position, height, weight, birth_date, college) VALUES ('SOPJIO KOUGANG', 1200, 1500, 'A', 20, 200, 'august 13', 'Dschang univesite');
# request_sqluire 'date'
# request_sqluire_relative 'my_sqlite_request_sqluest'

# class MySqliterequest_sqluest

# end