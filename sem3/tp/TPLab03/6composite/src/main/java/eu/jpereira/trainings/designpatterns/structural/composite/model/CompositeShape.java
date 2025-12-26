package eu.jpereira.trainings.designpatterns.structural.composite.model;

import java.util.ArrayList;
import java.util.List;

/**
 * @author Joao Pereira
 * */
public abstract class CompositeShape extends Shape {

	List<Shape> shapes;

	public CompositeShape() {
		this.shapes = createShapesList();
	}

	@Override
	public CompositeShape asComposite() {
		return this;
	}

	public boolean removeShape(Shape shape) {
		return this.shapes.remove(shape);
	}

	public int getShapeCount() {
		return this.shapes.size();
	}

	public void addShape(Shape shape) {
		this.shapes.add(shape);
	}

	public List<Shape> getShapes() {
		return this.shapes;
	}

	public List<Shape> getShapesByType(ShapeType type) {
		List<Shape> found = new ArrayList<Shape>();
		for (Shape s : shapes) {
			if (s.getType().equals(type)) {
				found.add(s);
			}
		}
		return found;
	}

	public List<Shape> getLeafShapes() {
		List<Shape> leaves = new ArrayList<Shape>();
		for (Shape s : shapes) {
			if (s.asComposite() == null) {
				leaves.add(s);
			} else {
				leaves.addAll(s.asComposite().getLeafShapes());
			}
		}
		return leaves;
	}

	protected List<Shape> createShapesList() {
		return new ArrayList<Shape>();
	}
}