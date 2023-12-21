from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)


def db_connection():
    conn = None
    try:
        conn = sqlite3.connect('goals.sqlite')
    except sqlite3.error as e:
        print(e)
    return conn


@app.route('/ping', methods=['HEAD'])
def ping():
    # Return a successful response for the ping
    return '', 204


@app.route("/goals", methods=["GET"])
def get_all_goals():
    conn = db_connection()
    cursor = conn.cursor()
    cursor.execute("SELECT * from goals")
    goals = [
        dict(id=row[0], title=row[1], description=row[2], deadline=row[3], is_private=row[4], mini_goals=row[5])
        for row in cursor.fetchall()
    ]
    if goals is not None:
        return jsonify(goals)


@app.route('/add_goal/<int:id>', methods=['POST'])
def add_goal(id):
    conn = db_connection()
    cursor = conn.cursor()
    data = request.get_json()

    title = data.get('title')
    description = data.get('description')
    deadline = data.get('deadline')
    is_private = data.get('isPrivate')
    mini_goals = data.get('miniGoals', [])
    sql = """INSERT INTO goals(id, title, description, deadline, is_private, mini_goals) VALUES (?, ?, ?, ?, ?, ?)"""

    cursor.execute(sql, (id, title, description, deadline, is_private, ','.join(mini_goals)))

    conn.commit()

    return jsonify({"message": f"Goal with the id: {cursor.lastrowid} created successfully"})


@app.route('/update_goal/<int:id>', methods=['PUT'])
def update_goal(id):
    conn = db_connection()
    cursor = conn.cursor()
    data = request.get_json()

    title = data.get('title')
    description = data.get('description')
    deadline = data.get('deadline')
    is_private = data.get('isPrivate')
    mini_goals = data.get('miniGoals', [])

    sql = """UPDATE goals SET title=?, description=?, deadline=?, is_private=?, mini_goals=? WHERE id=?"""
    cursor.execute(sql, (title, description, deadline, is_private, ','.join(mini_goals), id))

    conn.commit()

    return f"Goal with the id: {cursor.lastrowid} successfully updated"


@app.route('/goals/<int:id>', methods=['DELETE', 'GET'])
def put_delete_get_goal(id):
    conn = db_connection()
    cursor = conn.cursor()
    if request.method == 'DELETE':
        sql = """DELETE from goals WHERE id=?"""
        cursor.execute(sql, (id,))

        conn.commit()

        return f"Goal with the id: {cursor.lastrowid} successfully deleted", 200
    elif request.method == 'GET':
        sql = """SELECT * from goals WHERE id=?"""
        cursor.execute(sql, (id,))
        goal = cursor.fetchone()

        if goal is not None:
            goal_dict = {
                'id': goal[0],
                'title': goal[1],
                'description': goal[2],
                'deadline': goal[3],
                'is_private': goal[4],
                'mini_goals': goal[5]
            }
            return jsonify(goal_dict)
        else:
            return jsonify({'error': 'Goal not found'}), 404


if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)
