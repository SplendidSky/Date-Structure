from wtforms import StringField, SubmitField
from wtforms.validators import Required
from flask.ext.wtf import Form
from app import db

class NameForm(Form):
    name = StringField("What's your name?", validators = [Required()])
    submit = SubmitField("Submit")
