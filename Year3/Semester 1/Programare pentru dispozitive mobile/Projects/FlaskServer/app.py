from flask import Flask, request, jsonify
from flask_sqlalchemy import SQLAlchemy
from flask_cors import CORS
import logging

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///goals.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)
CORS(app)

logging.basicConfig(level=logging.DEBUG)

class Goal(db.Model):
    __tablename__ = 'goals'
    id = db.Column(db.Integer, primary_key=True)
    title = db.Column(db.String(50), unique=True, nullable=False)
    description = db.Column(db.String(255))
    deadline = db.Column(db.String(10))
    is_private = db.Column(db.Boolean)
    mini_goals = db.Column(db.String(255))


@app.route('/goals', methods=['GET'])
def get_all_goals():
    logging.info(f"Received GET request at /goals from {request.remote_addr}")
    __tablename__ = 'goals'
    goals = Goal.query.all()
    goals_json = [{'title': goal.title, 'description': goal.description,
                   'deadline': goal.deadline, 'is_private': goal.is_private,
                   'mini_goals': goal.mini_goals} for goal in goals]
    return jsonify(goals_json)


@app.route('/goals/<title>', methods=['GET'])
def get_goal_by_title(title):
    __tablename__ = 'goals'
    goal = Goal.query.filter_by(title=title).first()
    if goal:
        return jsonify({'title': goal.title, 'description': goal.description,
                        'deadline': goal.deadline, 'is_private': goal.is_private,
                        'mini_goals': goal.mini_goals})
    return jsonify({'message': 'Goal not found'}), 404


@app.route('/goals', methods=['POST'])
def insert_goal():
    __tablename__ = 'goals'
    data = request.get_json()
    new_goal = Goal(**data)
    db.session.add(new_goal)
    db.session.commit()
    return jsonify({'message': 'Goal inserted successfully'}), 201


@app.route('/goals/<id>', methods=['DELETE'])
def delete_goal(id):
    __tablename__ = 'goals'
    goal = Goal.query.get_or_404(id)
    if goal:
        db.session.delete(goal)
        db.session.commit()
        return jsonify({'message': 'Goal deleted successfully'})
    return jsonify({'message': 'Goal not found'}), 404


@app.route('/goals/<id>', methods=['PUT'])
def update_goal(id):
    __tablename__ = 'goals'
    goal = Goal.query.get_or_404(id)
    if goal:
        data = request.get_json()
        goal.title = data.get('title', goal.title)
        goal.description = data.get('description', goal.description)
        goal.deadline = data.get('deadline', goal.deadline)
        goal.is_private = data.get('is_private', goal.is_private)
        goal.mini_goals = data.get('mini_goals', goal.mini_goals)
        db.session.commit()
        return jsonify({'message': 'Goal updated successfully'})
    return jsonify({'message': 'Goal not found'}), 404


if __name__ == '__main__':
    db.create_all()
    app.run(debug=True, host="0.0.0.0")
