require 'csv'

class MySqliteRequest
    attr_reader :type_of_query

    def initialize(table_name = nil)
        @columns = nil
        @id = nil
        @table = nil

        @table_name = table_name
        @table_name = "#{table_name}.csv" unless @table_name.nil? || @table_name.end_with?('.csv')
        @type_of_query = nil
        @select_columns = []
        @where_conditions = []
        @join_data = []
        @order_direction_column = []
        @insert_values = nil
        # @update_table = nil
        @update_set = nil
        @delete_table = nil
       
    end

    def from(table_name)
        @table_name = table_name
        @table_name = "#{table_name}.csv" unless @table_name.nil? || @table_name.end_with?('.csv')

        self
    end

    # def select([column_name_a, column_name_b])
    def select(*columns)
        @type_of_query = :select
        @select_columns.concat(columns.map(&:to_sym))
        self
    end

    def where(column_name, criteria)
        @where_conditions << [column_name.to_sym, criteria]
        self
    end

    def join(column_on_db_a, tablename_db_b, column_db_b)
        @join_data = [column_on_db_a.to_sym, tablename_db_b, column_db_b.to_sym]
        self
    end

    def order(order='ASC', column_name)
        # retourne nil si order n est pas l une de ces valeurs
        order = order.upcase
        return nil unless ['DESC', 'ASC'].include?(order)
        # @order_direction = order.to_sym
        @order_direction_column = [order.to_sym, column_name.to_sym]
        self
    end

    def insert(table_name)
        @type_of_query ||= :insert
        @table_name = table_name
        @table_name = "#{table_name}.csv" unless @table_name.nil? || @table_name.end_with?('.csv')

        self
    end

    def values(*data)
        @insert_values = data
        self
    end

    def update(table_name)
        @type_of_query ||= :update
        @table_name = table_name
        @table_name = "#{table_name}.csv" unless @table_name.nil? || @table_name.end_with?('.csv')

        self
    end

    def set(data)
        # data is suppose to be and hash, we tranform all keys in symbol
        @update_set = data.transform_keys(&:to_sym)        
        self
    end

    def delete
        @type_of_query ||= :delete
        self
    end
    
    def run
        @table, @columns = form_table(@table_name)
        case @type_of_query
        when :select
          run_select
        when :insert
            insertion_db
        when :update
            update_db
        when :delete
            delete_db
        end
    end
    
    private
    
    def form_table(table_name)
        # convertion des datas du csv n un tableau plus interpreable
        table_result = {}
        columns = nil
        File.foreach(table_name).with_index do |line, idx|
          if idx.zero?
            columns = line.chomp.split(',').map(&:to_sym) 
            columns << :id
          else
            current_row = {}
            CSV.parse_line(line).each_with_index { |val, i| current_row[columns[i]] = val }
            current_row[:id] = idx
            table_result[idx] = current_row
          end
        end
        @id = table_result.size + 1
        [table_result, columns]
    end

    def run_select
        filter = select_where
        if @select_columns.include?(:*)
          selec = filter.map { |_id, row| row }
        else
          selec = filter.map { |_id, row| row.select { |k, _v| @select_columns.include?(k) } }
        end
        order_table(selec)
    end

    def order_table(table)
        return table if @order_direction_column.empty?
    
        table.sort do |a, b|
          tmp ||= 0
          @order_direction_column.each do |order, column|
            tmp = sort_column(a[column], b[column], order)
            break unless res.zero?
          end
          tmp
        end
    end

    def select_where
        return @table if @where_conditions.empty?
    
        @table.select do |_, row|
          check_where(row)
        end
    end

    def check_where(row)
        @where_conditions.all? do |where| 
          if where[1].is_a? Array
            where[1].include?(row[where[0]])
          else
            row[where[0]] == where[1] 
          end
        end
    end

    def insertion_db
        new_row = {}
        @columns[0...-1].each.with_index { |col, i| new_row[col] = @insert_values[i] }
        @table[@id] = new_row
        @id += 1
        modif_db
    end

    def update_db
        if @where_conditions.empty?
          @table.each { |_id, row| line_update(row) }
        else
          @table.select do |_, row|
            line_update(row) if check_where(row)
          end
        end
        modif_db
    end

      def line_update(row)
        @update_set.each { |key, val| row[key] = val }
      end

    def modif_db
        CSV.open(@table_name, 'w') do |csv|
            # through all columns without last column
          csv << @columns[0...-1]
          @table.each { |_id, row| csv << row.reject { |k, _val| k == :id }.values }
        end
    end

    def delete_db
        if @where_conditions.empty?
          @table = {}
        else
          delete_rows
        end
        modif_db
      end
    
      def delete_rows
        @table.each do |id, row|
          @table.delete(id) if check_where(row)
        end
      end
    # select test is ok
    # delete test is ok
    # insert test is ok
    # update test is ok
    # 
end

# select test success
request_select = MySqliteRequest.new
request_select = request_select.from('nba_player_data.csv')
request_select = request_select.select('name')
request_select = request_select.where('college', 'Dschang school university')
# response_select = request_select.run
# puts "reponse:#{response_select}"

# _delete test success
request_delete = MySqliteRequest.new
request_delete = request_delete.delete
request_delete = request_delete.from('nba_player_data.csv')
request_delete = request_delete.where('college', 'Duke University')
# request_delete.run

# test insert success
request_insert = MySqliteRequest.new
request_insert = request_insert.insert('nba_player_data.csv')
request_insert = request_insert.values(name = 'sopjio rochnel', year_start = 2015, year_end = 2016, position ='S', height = 150, weight = 50, birth_date = "august 13", college = 'Dschang school university')
# request_insert.run

# update test succes
request_update = MySqliteRequest.new
request_update = request_update.from('nba_player_data.csv')
request_update = request_update.update('nba_player_data.csv')
request_update = request_update.set('height': 250)
request_update = request_update.where('college', 'Dschang school university')
# request_update.run



